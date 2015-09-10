#include <iostream>
#include <SDL/SDL.h>

void fatalError(std::string error)
{
	printf(error.c_str());
	std::cout << "\nPress any key to exit...";
	int temp;
	std::cin >> temp;
	SDL_Quit();
	exit(1);
}