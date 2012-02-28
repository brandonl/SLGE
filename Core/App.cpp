#include "App.h"
#include <sstream>
#include "Settings.h"

using namespace slge;

App::App() 
{
}

App::~App()
{
}

void App::init( const std::string&& name, unsigned && width, unsigned&& height  )
{
	window.init( name, width, height, 32, 24 );
	input.init();
	scene->init();
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

	while( appIsRunning && Window::isOpen() )
	{
        Window::update();

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
			timeSinceLastUpdate = 0;
		}

		Window::clear();
		scene->draw();
		Window::swapBuffers();
		getFPS();
	}
}
