#pragma once
#include <stdio.h>
#include <glew.h>
#include "CommonValues.h"

class Texture
{
public:
	Texture() : textureID(0), width(0), height(0), bitDepth(0), fileLocation(nullptr) {}
	Texture(const char* fileLoc) : Texture() { fileLocation = fileLoc; }

	bool LoadTexture() { return Load(); }
	bool LoadTextureA() { return Load(); }

	void UseTexture()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void ClearTexture()
	{
		if (textureID) glDeleteTextures(1, &textureID);
		textureID = 0;
	}

private:
	GLuint textureID;
	int width, height, bitDepth;
	const char* fileLocation;

	// Siempre se carga como RGBA para que cualquier formato (png, tga, jpg) funcione igual
	bool Load()
	{
		unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 4);
		if (!texData)
		{
			printf("No se pudo cargar la textura: %s\n", fileLocation);
			return false;
		}
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(texData);
		return true;
	}
};
