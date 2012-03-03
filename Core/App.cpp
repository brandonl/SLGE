#include <sstream>
#include "App.h"
#include "Settings.h"
using namespace slge;

//Does not exhibit perfect fowarding.
App::App( const std::string& name, unsigned width, unsigned height ) 
	:	window( Window( name, width, height, 32, 24 ) )
{
	input.init();
}

App::~App()
{
}

void App::run()
{
	bool debug = false;
	double lastTick = Window::tick();
	double timeSinceLastUpdate = 0.0;
   bool appIsRunning = true;

	while( appIsRunning && window.isOpen() )
	{
		window.update();

		timeSinceLastUpdate += Window::tick() - lastTick;
		lastTick = Window::tick();
		if( timeSinceLastUpdate >= DELTA_TIME )
		{
			Input::update();

			if( Input::isKeyPressed( Input::ESC ) )
				appIsRunning = false;

			if( Input::isKeyPressed( 'D' ) )
			{
				debug = ( !debug ? true : false );
				scene->changeLayer( ( debug ? Scene::debug : Scene::noDebug ) );
			}

			scene->update();
			timeSinceLastUpdate = 0.0;
		}

		window.clear();
		scene->draw();
		window.swapBuffers();
		getFPS();
	}

	window.close();
}

std::string App::getFPS()
{
   static std::string title = "";
   static double FPS = 60.;
   double nextSec = 0.0;
   static double prevSec = 0.0;

   FPS++;
   nextSec = Window::tick();

   if( nextSec - prevSec > 1.0 )
   {
		prevSec = nextSec;
		std::stringstream ss;
		ss << FPS << " FPS";
		ss >> title;
		FPS = 0.;
   }
	return title;
}

double App::getGameSpeed()
{
	return FIXED_UPDATE_SPEED;
}
