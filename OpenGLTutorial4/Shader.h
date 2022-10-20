#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Minicore.h"

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		ShaderProgram = glCreateProgram();
		if (ShaderProgram == 0)
		{
			std::cout << "Error creating shader program!" << std::endl;
			exit(-1);
		}
		CompileShaderFromFile(vertexPath, GL_VERTEX_SHADER);
		CompileShaderFromFile(fragmentPath, GL_FRAGMENT_SHADER);
		LinkShaderProgram();
	}
	~Shader()
	{
		glDeleteProgram(ShaderProgram);
	}

	
	/*
	Shader& GetShader()
	{
		return *this;
	}
	*/
	void UseProgram()
	{
		glUseProgram(ShaderProgram);
	}
	void SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), static_cast<int>(value));
	}
	void SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value);
	}
	void SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value);
	}
	void Set4Float(const std::string& name, float value1, float value2, float value3, float value4) const
	{
		glUniform4f(glGetUniformLocation(ShaderProgram, name.c_str()), value1, value2, value3, value4);
	}
	void SetMatrix4fv(const std::string& name, float*) const
	{

	}
private:
	GLuint ShaderProgram;
	void CompileShaderFromFile(const char* path, GLenum shaderType)
	{
		std::string code;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			shaderFile.open(path);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
			code = shaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}
		const GLchar* shaderCode = code.c_str();
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderCode, NULL);
		glCompileShader(shader);
		CheckErrors(shader, "SHADER", GL_COMPILE_STATUS);
		glAttachShader(ShaderProgram, shader);
		glDeleteShader(shader);
	}
	void CheckErrors(GLuint obj, std::string type, int checkStatus )
	{
		GLint success;
		if (type == "SHADER"){CheckErrorAndLog(glGetShaderiv, glGetShaderInfoLog)}
		else if (type == "PROGRAM"){CheckErrorAndLog(glGetProgramiv, glGetProgramInfoLog)}
	}
	void LinkShaderProgram()
	{
		glLinkProgram(ShaderProgram);
		CheckErrors(ShaderProgram, "PROGRAM", GL_LINK_STATUS);
#ifndef __APPLE__
		glValidateProgram(ShaderProgram);
		CheckErrors(ShaderProgram, "PROGRAM", GL_VALIDATE_STATUS);
#endif // !__APPLE__
	}
};