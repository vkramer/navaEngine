#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>

class Texture {

public:
	Texture(const char* fileName);
	~Texture();

	void bind() const;
	void unbind() const;

	int getTextureID();

private:
	unsigned int m_textureID;
	unsigned char* m_data;

	int m_width;
	int m_height;
	int m_nrChannels;

	GLenum m_textureTarget;

	static const Texture* s_lastBind;

};