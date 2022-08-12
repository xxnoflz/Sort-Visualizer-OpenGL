#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::Shaders;

void ResourceManager::LoadShader(const std::string vertexPath, const std::string fragmentPath, const std::string name) {
	std::fstream vertexFile{ vertexPath };
	std::stringstream vertexStream;
	vertexStream << vertexFile.rdbuf();
	const std::string vertexCode{ vertexStream.str() };

	std::fstream fragmentFile{ fragmentPath };
	std::stringstream fragmentStream;
	fragmentStream << fragmentFile.rdbuf();
	const std::string fragmentCode{ fragmentStream.str() };

	Shader shader;
	shader.CreateShader(vertexCode, fragmentCode);
	Shaders[name] = shader;
}

Shader& ResourceManager::GetShader(const std::string name) {
	return Shaders[name];
}