#pragma once

#define NULL_SCREEN_INDEX -1

class IMainGame;

enum class ScreenState
{
	NONE,
	RUNNING,
	EXIT_APPLICATION,
	MOVE_TO_NEXT,
	MOVE_TO_PREVIOUS
};

class IGameScreen
{
public:
	friend class ScreenList;

	IGameScreen() {/*Empty for now*/ }
	virtual ~IGameScreen() {/*Empty for now*/}

	//Returns the index of next or previous screen when changing screens
	virtual int getNextScreenIndex() const = 0;
	virtual int getPreviousScreenIndex() const = 0;

	virtual void build() = 0;	//< Called at beginning of application
	virtual void destroy() = 0;	//< Called at end of application
	virtual void onEntry() = 0;	//< Called at entrance of screen
	virtual void onExit() = 0;	//< Called at exit of screen

	//Called in main game loop
	virtual void update() = 0;
	virtual void render() = 0;

	int getScreenIndex() const { return _screenIndex; }
	ScreenState getState() const { return _currentState; }

	void setParentGame(IMainGame* game) { _game = game; }
	void setRunning() { _currentState = ScreenState::RUNNING; }

protected:
	IMainGame* _game = nullptr;
	ScreenState _currentState = ScreenState::NONE;
	int _screenIndex = -1;
};

