#pragma once

class Game {

public:
	Game() {}
	virtual ~Game() {}

	virtual void init() {}
	virtual void update() {}
	virtual void render() {}

private:

};