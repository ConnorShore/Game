#include "IMainGame.h"
#include "ScreenList.h"
#include "IGameScreen.h"
#include "Timing.h"


IMainGame::IMainGame()
{
	_screenList = std::make_unique<ScreenList>(this);
}

bool IMainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	if (!initSystems()) return false;

	initSystems();
	onInit();

	addScreens();
	_currentScreen = _screenList->getCurrent();
	_currentScreen->onEntry();
	_currentScreen->setRunning();

	return true;
}

bool IMainGame::initSystems()
{
	_window.createWindow("New Game", 1280, 720, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0);
	return true;
}

void IMainGame::onSDLEvent(SDL_Event& evnt)
{
	switch (evnt.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;

		case SDL_KEYDOWN:
			_inputManager.keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.keyReleased(evnt.key.keysym.sym);
			break;

		case SDL_MOUSEMOTION:
			_inputManager.setMousePos(glm::vec2(evnt.motion.x, evnt.motion.y));
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.keyPressed(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.keyReleased(evnt.button.button);
			break;
	}
}

void IMainGame::update()
{
	if (_currentScreen) {
		switch (_currentScreen->getState()) {
			case ScreenState::RUNNING:
				_currentScreen->update();
				break;
			case ScreenState::MOVE_TO_NEXT:
				_currentScreen->onExit();
				_currentScreen = _screenList->moveNext();
				if (_currentScreen) {
					_currentScreen->setRunning();
					_currentScreen->onEntry();
				}
				break;
			case ScreenState::MOVE_TO_PREVIOUS:
				_currentScreen->onExit();
				_currentScreen = _screenList->movePrevious();
				if (_currentScreen) {
					_currentScreen->setRunning();
					_currentScreen->onEntry();
				}
				break;
			case ScreenState::EXIT_APPLICATION:
				exitGame();
				break;
			default:
				break;
		}
	}
	else {
		exitGame();
	}
}

void IMainGame::render()
{
	glViewport(0, 0, _window.getWidth(), _window.getHeight());

	if (_currentScreen && _currentScreen->getState() == ScreenState::RUNNING) {
		_currentScreen->render();
	}
}

void IMainGame::run()
{
	if (!init()) return;
	Timing _timer;

	_isRunning = true;

	_timer.TimeInit();

	while (_isRunning) {
		_timer.FpsLimitInit();
		_timer.calcDeltaTime();

		_inputManager.update();
		update();
		render();

		_timer.CalculateFPS(false);
		_timer.LimitFPS(60.0f);
		_window.swapWindow();
	}
}

void IMainGame::exitGame()
{
	if (_screenList) {
		_screenList->destroy();
		_screenList.reset();	//removes _screenList from memory
	}

	_isRunning = false;
}

IMainGame::~IMainGame()
{
}