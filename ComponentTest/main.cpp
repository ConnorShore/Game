#include <iostream>

#include "Entity.h"

int main(int argc, char** argv)
{
	Entity* test = new Entity("Entity1");

	test->serialize("Entity1.txt");

	int tmp;
	std::cin >> tmp;
	return 0;
}