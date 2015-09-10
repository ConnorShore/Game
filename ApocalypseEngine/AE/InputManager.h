#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <GL/glew.h>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void keyPressed(unsigned int keyID);
	void keyReleased(unsigned int keyID);
	bool isKeyDown(unsigned int keyID);

	void setMousePos(glm::vec2& coords);

	//getters
	glm::vec2 getMousePos() const { return _mousePos; }
	float getMouseX() const  { return _mousePos.x; }
	float getMouseY() const  { return _mousePos.y; }

private:
	GLuint _keyID;
	std::unordered_map<unsigned int, bool> _keyMap;

	glm::vec2 _mousePos;
};

