#define WIN32_LEAN_AND_MEAN
#define VC_LEANMEAN

#include "App.h"
#include <iostream>
#include "Earth.h"
using namespace slge;

int main()
{
	App env;
	env.set( new home() );
	std::cout << "Set Scene..." << std::endl;

	// This order MUST be maintained.
	// Initializing app must take place after scene.
	// TODO: Create Macro to aid in this invariant.
	env.init( std::string( "SLGE" ), 480u, 640u );
	std::cout << "Inited app..." << std::endl;
	env.run();
	std::cout << "Game Exited" << std::endl;
	return 0;
}
