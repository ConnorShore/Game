#include "InputManager.h"


InputManager::InputManager() : _mousePos(0.0f)
{
}

void InputManager::keyPressed(unsigned int keyID)
{
	_keyMap[keyID] = true;
}

void InputManager::keyReleased(unsigned int keyID)
{
	_keyMap[keyID] = false;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto mit = _keyMap.find(keyID);

	if (mit != _keyMap.end()) {
		return mit->second;
	}
	else {
		return false;
	}
}

void InputManager::setMousePos(glm::vec2& coords)
{
	_mousePos = coords;
}

InputManager::~InputManager()
{
}
