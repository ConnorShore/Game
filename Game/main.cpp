#include <iostream>

#include "MainGame.h"

int main(int argc, char** argv)
{
	MainGame game;
	game.run();

	std::cout << "Hello World!";

	int temp;
	std::cin >> temp;
	return 0;
}