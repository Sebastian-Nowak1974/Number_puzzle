#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Shader
{
public:
	Shader();
	void deleteShader();
	void useProgram() const;
	inline GLuint getShaderID() const { return m_shaderID; }

private:
	GLuint m_shaderID{ 0 };
};
