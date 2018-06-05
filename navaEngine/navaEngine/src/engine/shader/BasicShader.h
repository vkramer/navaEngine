#pragma once

#include "Shader.h"

class BasicShader : public Shader
{

public:
	static BasicShader* getInstance()
	{
		static BasicShader instance;
		return &instance;
	}

	void updateUniforms(Transform& transform, Model& model, RenderingEngine* renderingEngine);

private:
	BasicShader();

};
