#pragma once

#include "../Component.h"
#include "../model/Model.h"
#include "../../shader/Shader.h"

class Shader;

class Renderer : public Component
{
public:
	Renderer(Model* model, Shader* shader);
	virtual ~Renderer() {}

	//virtual void render();
	virtual void render(RenderingEngine* renderingEngine);

private:
	Model* m_model;
	Shader* m_shader;
};