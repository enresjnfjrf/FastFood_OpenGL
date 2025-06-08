#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	const char* vShaderCode;
	const char* fShaderCode;

	std::string vTempString;
	std::string fTempString;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		std::stringstream vShaderStream;
		vShaderFile.open(vertexPath);
		vShaderStream << vShaderFile.rdbuf();
		vShaderFile.close();
		vTempString = vShaderStream.str();
		vShaderCode = vTempString.c_str();

		std::stringstream fShaderStream;
		fShaderFile.open(fragmentPath);
		fShaderStream << fShaderFile.rdbuf();
		fShaderFile.close();
		fTempString = fShaderStream.str();
		fShaderCode = fTempString.c_str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	unsigned int vertex;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	unsigned int fragment;
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	programID = glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Shader::Use()
{
	glUseProgram(programID);
}

unsigned int Shader::ID()
{
	return programID;
}

void Shader::SetMatrix4F(const std::string& name, glm::mat4& m)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::SetVec2(const std::string& name, glm::vec2 vec)
{
	glUniform2f(glGetUniformLocation(programID, name.c_str()), vec[0], vec[1]);
}

void Shader::SetVec3(const std::string& name, glm::vec3 vec)
{
	glUniform3f(glGetUniformLocation(programID, name.c_str()), vec[0], vec[1], vec[2]);
}

void Shader::SetVec4(const std::string& name, glm::vec4 vec)
{
	glUniform4f(glGetUniformLocation(programID, name.c_str()), vec[0], vec[1], vec[2], vec[3]);
}

void Shader::SetFloat(const std::string& name, float f)
{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), f);
}

void Shader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}