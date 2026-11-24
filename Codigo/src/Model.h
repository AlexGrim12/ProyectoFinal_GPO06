#pragma once
#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh_tn.h"
#include "Texture.h"

class Model
{
public:
	Model() {}

	void LoadModel(const std::string& fileName)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(fileName,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
		if (!scene)
		{
			printf("Fallo al cargar el modelo %s: %s\n", fileName.c_str(), importer.GetErrorString());
			return;
		}
		LoadNode(scene->mRootNode, scene);
		LoadMaterials(scene);
	}

	void RenderModel()
	{
		for (size_t i = 0; i < meshList.size(); i++)
		{
			unsigned int materialIndex = meshToTex[i];
			if (materialIndex < textureList.size() && textureList[materialIndex])
				textureList[materialIndex]->UseTexture();
			meshList[i]->RenderMeshModel();
		}
	}

	void ClearModel()
	{
		for (auto* m : meshList) { if (m) { m->ClearMeshModel(); delete m; } }
		meshList.clear();
		textureList.clear();
		meshToTex.clear();
	}

private:
	std::vector<MeshModel*> meshList;
	std::vector<Texture*> textureList;
	std::vector<unsigned int> meshToTex;

	// Cache global: varias piezas comparten la misma textura y no se carga dos veces.
	static Texture* CargarTextura(const std::string& ruta)
	{
		static std::map<std::string, Texture*> cache;
		auto it = cache.find(ruta);
		if (it != cache.end()) return it->second;

		std::string* persistente = new std::string(ruta);
		Texture* t = new Texture(persistente->c_str());
		if (!t->LoadTextureA())
		{
			delete t;
			t = nullptr;
		}
		cache[ruta] = t;
		return t;
	}

	void LoadNode(aiNode* node, const aiScene* scene)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
			LoadMesh(scene->mMeshes[node->mMeshes[i]]);
		for (size_t i = 0; i < node->mNumChildren; i++)
			LoadNode(node->mChildren[i], scene);
	}

	void LoadMesh(aiMesh* mesh)
	{
		std::vector<GLfloat> vertices;
		std::vector<unsigned int> indices;

		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
			if (mesh->mTextureCoords[0])
				vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
			else
				vertices.insert(vertices.end(), { 0.0f, 0.0f });
			// Convencion del curso: la normal se invierte (el shader usa la direccion luz->fragmento)
			if (mesh->mNormals)
				vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
			else
				vertices.insert(vertices.end(), { 0.0f, 0.0f, 0.0f });
		}
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		MeshModel* newMesh = new MeshModel();
		newMesh->CreateMeshModel(vertices.data(), indices.data(), (unsigned int)vertices.size(), (unsigned int)indices.size());
		meshList.push_back(newMesh);
		meshToTex.push_back(mesh->mMaterialIndex);
	}

	void LoadMaterials(const aiScene* scene)
	{
		textureList.resize(scene->mNumMaterials, nullptr);
		for (size_t i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* material = scene->mMaterials[i];
			if (material->GetTextureCount(aiTextureType_DIFFUSE))
			{
				aiString path;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
				{
					std::string p(path.data);
					size_t idx = p.find_last_of("/\\");
					std::string nombre = (idx == std::string::npos) ? p : p.substr(idx + 1);
					if (!nombre.empty() && nombre[0] != '*')
						textureList[i] = CargarTextura("Textures/" + nombre);
				}
			}
			if (!textureList[i])
				textureList[i] = CargarTextura("Textures/plain.png");
		}
	}
};
