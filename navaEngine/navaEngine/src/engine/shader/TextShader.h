#pragma once

#include "Shader.h"

class TextShader : public Shader {

public:
	static TextShader* getInstance() {
		static TextShader instance;
		return &instance;
	}

	virtual void updateX();

private:
	TextShader();
};
