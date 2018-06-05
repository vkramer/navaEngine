#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "../texture/Texture.h"
#include "../scenegraph/Transform.h"
#include "../components/model/Model.h"
#include "../core/RenderingEngine.h"

class Shader {

public:
	Shader();
	virtual ~Shader();

	void bind();
	void unbind();

	void addVertexShaderFromFile(const std::string& fileName);
	void addFragmentShaderFromFile(const std::string& fileName);
	void addGeometryShaderFromFile(const std::string& fileName);

	void addVertexShader(const std::string& text);
	void addFragmentShader(const std::string& text);
	void addGeometryShader(const std::string& text);

	void addProgram(const std::string& text, int type);
	void compileShader();

	void addUniform(const std::string& uniformName);

	void setAttributeLocation(const std::string& attributeName, int location);
	void setUniformi(const std::string& name, int value);
	void setUniformf(const std::string& name, float value);
	void setUniform(const std::string& name, const glm::mat4& value);
	void setUniform(const std::string& name, const glm::vec3& value);

	virtual void updateUniforms(Texture* texture);
	virtual void updateUniforms(Transform& transform, Model& model);
	virtual void updateUniforms(Transform& transform, Model& model, RenderingEngine* renderingEngine);
	virtual void updateX();

private:
	unsigned int m_programID;
	std::map<std::string, int> m_uniforms;
	std::vector<int> m_shaders;

};

