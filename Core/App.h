#ifndef APP_H
#define APP_H

#include "Window.h"
#include "Input.h"
#include "Scene.h"
#include <string>
#include "ResourceModule.h"
#include "Utils.h"

namespace slge
{
	class App : private Uncopyable
	{
		public:
			App();
			~App();

			void run();
			void init( const std::string&& name, unsigned&& width, unsigned&& height );
			void set( Scene* scene );
	
		private:
			Window window;
			Input input;
			Resources resources;
			std::unique_ptr<Scene> scene;
	};

	inline void App::set( Scene* s )
	{
		scene.reset( s );
	}
};
#endif
