#pragma once
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <glew.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>

#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
public:
	Shader() : shaderID(0), uniformModel(0), uniformProjection(0), uniformView(0), uniformEyePosition(0),
		uniformColor(0), uniformSpecularIntensity(0), uniformShininess(0),
		uniformPointLightCount(0), uniformSpotLightCount(0) {}

	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
	{
		std::string vs = ReadFile(vertexLocation);
		std::string fs = ReadFile(fragmentLocation);
		CompileShader(vs.c_str(), fs.c_str());
	}

	void CreateFromString(const char* vertexCode, const char* fragmentCode)
	{
		CompileShader(vertexCode, fragmentCode);
	}

	GLuint GetProjectionLocation() { return uniformProjection; }
	GLuint GetModelLocation() { return uniformModel; }
	GLuint GetViewLocation() { return uniformView; }
	GLuint GetEyePositionLocation() { return uniformEyePosition; }
	GLuint getColorLocation() { return uniformColor; }
	GLuint GetSpecularIntensityLocation() { return uniformSpecularIntensity; }
	GLuint GetShininessLocation() { return uniformShininess; }

	void UseShader() { glUseProgram(shaderID); }

	void ClearShader()
	{
		if (shaderID != 0) glDeleteProgram(shaderID);
		shaderID = 0;
	}

	void SetDirectionalLight(DirectionalLight* dLight)
	{
		glUniform3f(uniformDirectionalLight.color, dLight->color.x, dLight->color.y, dLight->color.z);
		glUniform1f(uniformDirectionalLight.ambientIntensity, dLight->ambientIntensity);
		glUniform1f(uniformDirectionalLight.diffuseIntensity, dLight->diffuseIntensity);
		glUniform3f(uniformDirectionalLight.direction, dLight->direction.x, dLight->direction.y, dLight->direction.z);
	}

	void SetPointLights(PointLight* pLight, unsigned int lightCount)
	{
		if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;
		glUniform1i(uniformPointLightCount, lightCount);
		for (unsigned int i = 0; i < lightCount; i++)
		{
			glUniform3f(uniformPointLight[i].color, pLight[i].color.x, pLight[i].color.y, pLight[i].color.z);
			glUniform1f(uniformPointLight[i].ambientIntensity, pLight[i].ambientIntensity);
			glUniform1f(uniformPointLight[i].diffuseIntensity, pLight[i].diffuseIntensity);
			glUniform3f(uniformPointLight[i].position, pLight[i].position.x, pLight[i].position.y, pLight[i].position.z);
			glUniform1f(uniformPointLight[i].constant, pLight[i].constant);
			glUniform1f(uniformPointLight[i].linear, pLight[i].linear);
			glUniform1f(uniformPointLight[i].exponent, pLight[i].exponent);
		}
	}

	void SetSpotLights(SpotLight* sLight, unsigned int lightCount)
	{
		if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;
		glUniform1i(uniformSpotLightCount, lightCount);
		for (unsigned int i = 0; i < lightCount; i++)
		{
			glUniform3f(uniformSpotLight[i].color, sLight[i].color.x, sLight[i].color.y, sLight[i].color.z);
			glUniform1f(uniformSpotLight[i].ambientIntensity, sLight[i].ambientIntensity);
			glUniform1f(uniformSpotLight[i].diffuseIntensity, sLight[i].diffuseIntensity);
			glUniform3f(uniformSpotLight[i].position, sLight[i].position.x, sLight[i].position.y, sLight[i].position.z);
			glUniform1f(uniformSpotLight[i].constant, sLight[i].constant);
			glUniform1f(uniformSpotLight[i].linear, sLight[i].linear);
			glUniform1f(uniformSpotLight[i].exponent, sLight[i].exponent);
			glUniform3f(uniformSpotLight[i].direction, sLight[i].direction.x, sLight[i].direction.y, sLight[i].direction.z);
			glUniform1f(uniformSpotLight[i].edge, sLight[i].procEdge);
		}
	}

private:
	struct UniLight
	{
		GLint color = -1, ambientIntensity = -1, diffuseIntensity = -1;
		GLint direction = -1, position = -1, constant = -1, linear = -1, exponent = -1, edge = -1;
	};

	GLuint shaderID;
	GLuint uniformModel, uniformProjection, uniformView, uniformEyePosition, uniformColor;
	GLuint uniformSpecularIntensity, uniformShininess;
	GLint uniformPointLightCount, uniformSpotLightCount;
	UniLight uniformDirectionalLight;
	UniLight uniformPointLight[MAX_POINT_LIGHTS];
	UniLight uniformSpotLight[MAX_SPOT_LIGHTS];

	static std::string ReadFile(const char* path)
	{
		std::ifstream f(path, std::ios::in);
		if (!f.is_open())
		{
			printf("No se pudo leer el shader: %s\n", path);
			return "";
		}
		std::stringstream ss;
		ss << f.rdbuf();
		return ss.str();
	}

	void AddShader(GLuint program, const char* code, GLenum type)
	{
		GLuint s = glCreateShader(type);
		glShaderSource(s, 1, &code, NULL);
		glCompileShader(s);
		GLint ok = 0;
		glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
		if (!ok)
		{
			char log[1024] = { 0 };
			glGetShaderInfoLog(s, sizeof(log), NULL, log);
			printf("Error compilando shader %d: %s\n", (int)type, log);
			return;
		}
		glAttachShader(program, s);
	}

	GLint Loc(const std::string& name) { return glGetUniformLocation(shaderID, name.c_str()); }

	void CompileShader(const char* vertexCode, const char* fragmentCode)
	{
		shaderID = glCreateProgram();
		if (!shaderID)
		{
			printf("Error creando el programa de shaders\n");
			return;
		}
		AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
		AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

		GLint ok = 0;
		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &ok);
		if (!ok)
		{
			char log[1024] = { 0 };
			glGetProgramInfoLog(shaderID, sizeof(log), NULL, log);
			printf("Error enlazando shader: %s\n", log);
			return;
		}

		uniformModel = Loc("model");
		uniformProjection = Loc("projection");
		uniformView = Loc("view");
		uniformEyePosition = Loc("eyePosition");
		uniformColor = Loc("color");
		uniformSpecularIntensity = Loc("material.specularIntensity");
		uniformShininess = Loc("material.shininess");

		uniformDirectionalLight.color = Loc("directionalLight.base.color");
		uniformDirectionalLight.ambientIntensity = Loc("directionalLight.base.ambientIntensity");
		uniformDirectionalLight.diffuseIntensity = Loc("directionalLight.base.diffuseIntensity");
		uniformDirectionalLight.direction = Loc("directionalLight.direction");

		uniformPointLightCount = Loc("pointLightCount");
		for (int i = 0; i < MAX_POINT_LIGHTS; i++)
		{
			std::string b = "pointLights[" + std::to_string(i) + "].";
			uniformPointLight[i].color = Loc(b + "base.color");
			uniformPointLight[i].ambientIntensity = Loc(b + "base.ambientIntensity");
			uniformPointLight[i].diffuseIntensity = Loc(b + "base.diffuseIntensity");
			uniformPointLight[i].position = Loc(b + "position");
			uniformPointLight[i].constant = Loc(b + "constant");
			uniformPointLight[i].linear = Loc(b + "linear");
			uniformPointLight[i].exponent = Loc(b + "exponent");
		}

		uniformSpotLightCount = Loc("spotLightCount");
		for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
		{
			std::string b = "spotLights[" + std::to_string(i) + "].";
			uniformSpotLight[i].color = Loc(b + "base.base.color");
			uniformSpotLight[i].ambientIntensity = Loc(b + "base.base.ambientIntensity");
			uniformSpotLight[i].diffuseIntensity = Loc(b + "base.base.diffuseIntensity");
			uniformSpotLight[i].position = Loc(b + "base.position");
			uniformSpotLight[i].constant = Loc(b + "base.constant");
			uniformSpotLight[i].linear = Loc(b + "base.linear");
			uniformSpotLight[i].exponent = Loc(b + "base.exponent");
			uniformSpotLight[i].direction = Loc(b + "direction");
			uniformSpotLight[i].edge = Loc(b + "edge");
		}
	}
};
