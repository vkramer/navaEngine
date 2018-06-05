#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const Texture* Texture::s_lastBind = 0;

Texture::Texture(const char* fileName) {

	stbi_set_flip_vertically_on_load(true);

	m_data = stbi_load(fileName, &m_width, &m_height, &m_nrChannels, 3);

	if (m_data) {

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		GLenum format;
		if (m_nrChannels == 1)
			format = GL_RED;
		else if (m_nrChannels = 3)
			format = GL_RGB;
		else if (m_nrChannels = 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(m_data);

		std::cout << "Texture:: [" << fileName << "] - ID:: " << m_textureID << " - Loaded Successfully!" << std::endl;
	}
	else {
		std::cout << "Failed to load Texture: " << fileName << " :: REASON ( " << stbi_failure_reason() << " )" << std::endl;
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &m_textureID);
}

void Texture::bind() const {
	glActiveTexture(GL_TEXTURE0 + m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

}

void Texture::unbind() const {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getTextureID() {
	return m_textureID;
}
