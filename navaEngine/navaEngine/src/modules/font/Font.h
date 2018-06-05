#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../engine/shader/TextShader.h"

#include <map>
#include <string>

struct Character {
	GLuint textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint advance;
};

class Font {

public:
	Font(const GLchar *fontPath);
	virtual ~Font() {};

	void drawText(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
	GLuint VAO, VBO;
	std::map<GLchar, Character> characters;

	void initRenderData(const GLchar *fontPath);

};
