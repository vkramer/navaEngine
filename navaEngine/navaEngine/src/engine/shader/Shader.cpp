#include "Shader.h"

#include <cassert>
#include <fstream>
#include <glad/glad.h>

static void checkShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage);
static std::string loadShader(const std::string& fileName);

Shader::Shader() {
	m_programID = glCreateProgram();

	if (m_programID == 0) {
		std::cout << "[ERROR] :: Unable to create Shader Program" << std::endl;
		//exit(1);
	}
}

Shader::~Shader() {
	for (auto const& value : m_shaders) {
		glDetachShader(m_programID, value);
		glDeleteShader(value);
	}

	glDeleteProgram(m_programID);
}

void Shader::bind() {
	glUseProgram(m_programID);
}

void Shader::unbind() {
	glUseProgram(0);
}


// CLASS METHODS ---------------------------------------------------------------------------------------------------------
void Shader::addUniform(const std::string& uniformName) {
	unsigned int location = glGetUniformLocation(m_programID, uniformName.c_str());

	//assert(location != 0);

	m_uniforms.insert(std::pair<std::string, int>(uniformName, location));
}

void Shader::addVertexShaderFromFile(const std::string& fileName) {
	addVertexShader(loadShader(fileName));
}

void Shader::addFragmentShaderFromFile(const std::string& fileName) {
	addFragmentShader(loadShader(fileName));
}

void Shader::addGeometryShaderFromFile(const std::string& fileName) {
	addGeometryShader(loadShader(fileName));
}

void Shader::addVertexShader(const std::string& text) {
	addProgram(text, GL_VERTEX_SHADER);
}

void Shader::addFragmentShader(const std::string& text) {
	addProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::addGeometryShader(const std::string& text) {
	addProgram(text, GL_GEOMETRY_SHADER);
}

void Shader::addProgram(const std::string& text, int type) {
	int shader = glCreateShader(type);

	if (shader == 0) {
		std::cout << "[ERROR] :: Error creating shader // type = " << type << std::endl;
	}

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLchar infoLog[1024];

		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		fprintf(stderr, "[ERROR] :: Error compiling shader type %d: '%s'\n", shader, infoLog);
		//exit(1);
	}

	glAttachShader(m_programID, shader);
	m_shaders.push_back(shader);
}

void Shader::compileShader() {
	glLinkProgram(m_programID);
	checkShaderError(m_programID, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_programID);
	checkShaderError(m_programID, GL_VALIDATE_STATUS, true, "Invalid shader program");
}

void Shader::setAttributeLocation(const std::string& attributeName, int location) {
	glBindAttribLocation(m_programID, location, attributeName.c_str());
}

void Shader::setUniformi(const std::string& name, int value) {
	glUniform1i(m_uniforms.at(name), value);
}

void Shader::setUniformf(const std::string& name, float value) {
	glUniform1f(m_uniforms.at(name), value);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) {
	glUniform3f(m_uniforms.at(name), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const glm::mat4& value) {
	glUniformMatrix4fv(m_uniforms.at(name), 1, GL_FALSE, &(value[0][0]));
}

// --------------------------------------------------------------------------------------------------------------------

static void checkShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (!success) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cout << errorMessage << std::endl;
	}
}

static std::string loadShader(const std::string& fileName) {
	std::ifstream file;
	file.open(("res/shaders/" + fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "[ERROR] :: Unable to load Shader: " << fileName << std::endl;
	}

	return output;
}
