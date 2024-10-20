#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<stb/stb_image.h>

class Texture
{
public:
	Texture(int texSize, const char** textureFile);
	void bindTexture (int textureID) const;	
	~Texture()
	{
		delete[] m_textures;		
	}
	Texture(const Texture& texture) = delete;
	Texture& operator=(const Texture& texture) = delete;

private:
	int m_texSize{1};
	GLuint* m_textures{};
	const char** m_texFile{};


};
