#include "app.h"
#include <iostream>
#include "world.h"
#include <sstream>

using namespace slge;

app::app() : running(true)
{
}

app::~app()
{
}

void app::init( const std::string& name, unsigned int width, unsigned int height  )
{
	window_singleton.init( name, width, height, 32, 24 );
	input_singleton.init();
	world_singleton.init();
	resources_singleton.init();
}

void get_FPS()
{
   static std::string title = ""; 
   static int FPS = 60.0f;
   float next_sec = 0.0f;
   static float prev_sec = 0.0f;

   FPS++;
   next_sec = window::tick();				

   if( next_sec - prev_sec > 1.0f )
   {
		prev_sec = next_sec;
		std::stringstream ss;
		ss << FPS << " FPS";
		ss >> title;
		window::set_title(title);
		FPS = 0;
   }
}

void app::run()
{
	bool debug = false;
	double last_tick = window::tick();
	double time_since_last_update = 0.0;
    bool app_is_running = true;

	while( running && window::is_open() )
	{
        window::update();

		time_since_last_update += window::tick() - last_tick;
		last_tick = window::tick();
		if( time_since_last_update >= DELTA_TIME )
		{
			input::update();
			if( input::is_key_pressed( 257 ) )
				quit();
			if( input::is_key_pressed( 'D' ) )
			{ 
				debug = ( !debug ? true : false );
				world::change_layer( (debug ? 1 : 0 ) );
			}
			world::update();
			time_since_last_update = 0;
		}

		window::clear();
		world::draw();
		window::swap_buffers();
		get_FPS();
	}
}


void app::quit()
{
	running = false;
}

void app::set( scene* s )
{
	world::change_scene( s );
}
