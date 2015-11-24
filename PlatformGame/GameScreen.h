#pragma once

#include <ApocalypseEngine\IGameScreen.h>

class GameScreen : public IGameScreen
{
public:
	GameScreen();
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

	void input();
};