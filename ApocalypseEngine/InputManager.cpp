#include "InputManager.h"


InputManager::InputManager() : _mousePos(0.0f)
{
}

InputManager::~InputManager()
{
}

void InputManager::update()
{
	for (auto& it : _keyMap) {
		_previousKeyMap[it.first] = it.second;
	}
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

bool InputManager::isKeyPressed(unsigned int keyID)
{
	if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
		return true;
	}
	return false;
}

bool InputManager::wasKeyDown(unsigned int keyID)
{
	auto it = _previousKeyMap.find(keyID);
	if (it != _previousKeyMap.end()) {
		return it->second;
	}
	else {
		return false;
	}
}

void InputManager::setMousePos(glm::vec2& coords)
{
	_mousePos.x = coords.x;
	_mousePos.y = coords.y;
}
