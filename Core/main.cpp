#define WIN32_LEAN_AND_MEAN
#define VC_LEANMEAN

#include "app.h"
#include <iostream>
#include "earth.h"
using namespace slge;

int main()
{
	app env;
	env.init( "SLGE", 480, 640 );
	std::cout << "Inited app..." << std::endl;

	env.set( new home() );
	std::cout << "Set Scene..." << std::endl;

	env.run();
	std::cout << "Game Exited" << std::endl;
	return 0;
}
