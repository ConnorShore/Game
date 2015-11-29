#pragma once

#include "StaticShader.h"
#include "Box.h"
#include "Player.h"

#include <ApocalypseEngine\IGameScreen.h>
#include <ApocalypseEngine\SpriteBatch.h>
#include <ApocalypseEngine\ShaderProgram.h>
#include <ApocalypseEngine\Window.h>
#include <ApocalypseEngine\Camera2D.h>
#include <ApocalypseEngine\GLTexture.h>

#include <Box2D\Box2D.h>
#include <vector>

class GameScreen : public IGameScreen
{
public:
	GameScreen(Window* window);
	~GameScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update() override;
	virtual void render() override;

private:
	std::unique_ptr<b2World> _world;

	Window* _window;
	StaticShader _shader;
	SpriteBatch _spriteBatch;
	Camera2D _camera;
	GLTexture _boxTex;

	Player _player;

	std::vector<Box> _boxes;

	void input();
};