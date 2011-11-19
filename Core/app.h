#ifndef APP_H
#define APP_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "window.h"
#include "input.h"
#include "scene.h"
#include "world.h"
#include <string>
#include "resourcemodule.h"

namespace slge
{

	class app
	{
		public:
			explicit app();
			~app();

			void run();
			void init( const std::string& name, unsigned int width, unsigned int height );
			void set( scene* );

		private:
			void quit();
			window window_singleton;
			input input_singleton;
			world world_singleton;
			resources resources_singleton;
			bool running;
	};
};
#endif
