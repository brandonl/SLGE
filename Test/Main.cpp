#define WIN32_LEAN_AND_MEAN
#define VC_LEANMEAN

#include "App.h"
#include "Settings.h"
#include "Earth.h"
using namespace slge;

int main()
{
	{
		App env( std::string( "SLGE" ), INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT );
		env.set( new SplashScreen() );
		env.run();
	}

#ifndef NDEBUG
	char pauseForDEBUG = getchar();
#endif
	return 0;
}
