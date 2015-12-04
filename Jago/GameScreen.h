#pragma once

#include "StaticShader.h"
#include "LightShader.h"
#include "Box.h"
#include "Player.h"
#include "Torch.h"

#include <vector>

#include <Box2D\Box2D.h>

#include <ApocalypseEngine\IGameScreen.h>
#include <ApocalypseEngine\SpriteBatch.h>
#include <ApocalypseEngine\Window.h>
#include <ApocalypseEngine\Camera2D.h>
#include <ApocalypseEngine\GLTexture.h>
#include <ApocalypseEngine\Light2D.h>


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
	LightShader _lightShader;
	SpriteBatch _spriteBatch;
	GLTexture _dirt;
	Player _player;

	std::vector<Box> _boxes;
	std::vector<Torch*> _torches;

	void input();
};

