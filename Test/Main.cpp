#define WIN32_LEAN_AND_MEAN
#define VC_LEANMEAN

#include "App.h"
#include <cstdio>
#include "Earth.h"
using namespace slge;

int main()
{
	App env;
	env.set( new Home() );
	printf( "Set Scene...\n" );

	// This order MUST be maintained.
	// Initializing app must take place after scene.
	// TODO: Create Macro to aid in this invariant.
	env.init( std::string( "SLGE" ), 480u, 640u );
	printf( "Inited app...\n" );
	env.run();

	char c;
	c = getchar();
	return 0;
}
