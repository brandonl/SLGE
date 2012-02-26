#ifndef APP_H
#define APP_H

#include "Window.h"
#include "Input.h"
#include "Scene.h"
#include "World.h"
#include <string>
#include "ResourceModule.h"

namespace slge
{

	class App
	{
		public:
			App();
			~App();

			void run();
			void init( const std::string& name, unsigned int width, unsigned int height );
			void set( Scene* );

		private:
			void quit();
			Window window;
			Input input;
			World world;
			Resources resources;
			bool running;
	};
};
#endif
