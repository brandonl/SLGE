#ifndef APP_H
#define APP_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

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
			explicit App();
			~App();

			void run();
			void init( const std::string& name, unsigned int width, unsigned int height );
			void set( Scene* );

		private:
			void quit();
			Window windowSingleton;
			Input inputSingleton;
			World worldSingleton;
			Resources resourcesSingleton;
			bool running;
	};
};
#endif
