#define WIN32_LEAN_AND_MEAN
#define VC_LEANMEAN

#include "App.h"

#include "Earth.h"
using namespace slge;

int main()
{
	App env( std::string( "SLGE" ), 480u, 640u );
	env.set( new SplashScreen() );
	env.run();
	return 0;
}
