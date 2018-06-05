#include "Font.h"

#include "../../engine/components/model/Mesh.h"

#include <iostream>

Font::Font(const GLchar *fontPath)
{
	this->initRenderData(fontPath);
}

void Font::drawText(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {

	// Store Previous Blending State
	bool blend = glIsEnabled(GL_BLEND);

	// Store Previous SRC Alpha Blend Function
	GLint srcAlphaBlendFunc;
	glGetIntegerv(GL_BLEND_SRC_ALPHA, &srcAlphaBlendFunc);

	// Enable Blending
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader.bind();
	shader.updateX();

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);

	// Iterate through all input characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = characters[*c];

		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;
		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		GLfloat vertices[6][4] = {
			{ xpos,		ypos + h,	0.0, 0.0 },
		{ xpos,		ypos,		0.0, 1.0 },
		{ xpos + w,	ypos,		1.0, 1.0 },

		{ xpos,		ypos + h,	0.0, 0.0 },
		{ xpos + w,	ypos,		1.0, 1.0 },
		{ xpos + w,	ypos + h,	1.0, 0.0 }
		};

		//std::cout << "Glyph ID: " << ch.textureID << " loaded successfully!" << std::endl;

		// Render Glyph Texture over Quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Advance cursor for next glyph (advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale;
		//glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);
	//shader.unbind();

	// Restore Blending Options
	glBlendFunc(GL_SRC_ALPHA, srcAlphaBlendFunc);
	if (blend)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);


	//shader.unbind();
	//glDisable(GL_BLEND);

}

void Font::initRenderData(const GLchar *fontPath)
{
	FT_Library ft;
	FT_Face face;

	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR: FreeType could not init FreeType Library" << std::endl;
		return;
	}

	if (FT_New_Face(ft, fontPath, 0, &face))
	{
		std::cout << "ERROR: FreeType failed to load Font Face" << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	// Store Current Unpack Alignment
	GLint pixelStoreAlignment;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &pixelStoreAlignment);

	// Disable 4 byte alignment because we use one byte per pixel
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load the first 128 glyphs from font face
	for (GLubyte c = 0; c < 128; c++) 
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR: FreeType failed to load glyph" << std::endl;
			continue;
		}

		// For Each Glyph assign a Texture
		GLuint textureID;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			GL_RED, 
			face->glyph->bitmap.width, 
			face->glyph->bitmap.rows, 
			0, 
			GL_RED, 
			GL_UNSIGNED_BYTE, 
			face->glyph->bitmap.buffer
		);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		// Create Character struct for each glyph
		Character character = {
			textureID,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		// Insert character into character array
		characters.insert(std::pair<GLchar, Character>(c, character));
	}

	// Re-Enable Byte Alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, pixelStoreAlignment);

	// Unbind Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Discard Face and FreeType Objects
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// Create Mesh Object
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}