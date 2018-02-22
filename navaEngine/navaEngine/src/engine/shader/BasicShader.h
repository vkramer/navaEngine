#pragma once

#include "Shader.h"

class BasicShader : public Shader {

public:
	static BasicShader* getInstance() {
		static BasicShader instance;
		return &instance;
	}

private:
	BasicShader();

};
