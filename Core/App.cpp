#include "App.h"
#include <iostream>
#include "World.h"
#include <sstream>

using namespace slge;

App::App() : running(true)
{
}

App::~App()
{
}

void App::init( const std::string& name, unsigned int width, unsigned int height  )
{
	window.init( name, width, height, 32, 24 );
	input.init();
	world.init();
	resources.init();
}

void getFPS()
{
   static std::string title = "";
   static int FPS = 60;
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
		Window::setTitle(title);
		FPS = 0;
   }
}

void App::run()
{
	bool debug = false;
	double lastTick = Window::tick();
	double timeSinceLastUpdate = 0.0;
    bool appIsRunning = true;

	while( running && Window::isOpen() )
	{
        Window::update();

		timeSinceLastUpdate += Window::tick() - lastTick;
		lastTick = Window::tick();
		if( timeSinceLastUpdate >= DELTA_TIME )
		{
			Input::update();
			if( Input::isKeyPressed( Input::ESC ) )
				quit();
			if( Input::isKeyPressed( 'D' ) )
			{
				debug = ( !debug ? true : false );
				World::changeLayer( (debug ? 1 : 0 ) );
			}
			World::update();
			timeSinceLastUpdate = 0;
		}

		Window::clear();
		World::draw();
		Window::swapBuffers();
		getFPS();
	}
}


void App::quit()
{
	running = false;
}

void App::set( Scene* s )
{
	World::changeScene( s );
}
