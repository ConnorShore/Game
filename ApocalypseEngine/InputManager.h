#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <GL/glew.h>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void update();

	void keyPressed(unsigned int keyID);
	void keyReleased(unsigned int keyID);
	bool isKeyDown(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);

	void setMousePos(glm::vec2& coords);

	//getters
	glm::vec2 getMousePos() const { return _mousePos; }
	float getMouseX() const  { return _mousePos.x; }
	float getMouseY() const  { return _mousePos.y; }

private:
	GLuint _keyID;
	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _previousKeyMap;

	glm::vec2 _mousePos;

	bool wasKeyDown(unsigned int keyID);
};

