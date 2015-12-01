#pragma once

#include "StaticShader.h"
#include "Box.h"

#include <vector>

#include <Box2D\Box2D.h>

#include <ApocalypseEngine\IGameScreen.h>
#include <ApocalypseEngine\SpriteBatch.h>
#include <ApocalypseEngine\Window.h>
#include <ApocalypseEngine\Camera2D.h>
#include <ApocalypseEngine\GLTexture.h>

class GameScreen : public IGameScreen
{
public:
	GameScreen(Window* window);
	~GameScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;	//< Called at beginning of application
	virtual void destroy() override;	//< Called at end of application
	virtual void onEntry() override;	//< Called at entrance of screen
	virtual void onExit() override;	//< Called at exit of screen

	//Called in main game loop
	virtual void update() override;
	virtual void render() override;

private:
	std::unique_ptr<b2World> _world;

	Window* _window;
	Camera2D _camera;
	StaticShader _staticShader;
	SpriteBatch _spriteBatch;
	GLTexture _dirt;

	std::vector<Box> _boxes;

	void input();
};

