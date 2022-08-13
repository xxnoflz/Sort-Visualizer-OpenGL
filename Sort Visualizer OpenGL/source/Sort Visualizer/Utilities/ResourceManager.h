#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <map>

#include "Shader.h"

class ResourceManager {
public:
	static void LoadShader(const std::string vertexPath, const std::string fragmentPath, const std::string name);
	static Shader& GetShader(const std::string name);
private:
	static std::map<std::string, Shader> Shaders;

	ResourceManager();
};