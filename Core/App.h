#ifndef __APP_H__
#define __APP_H__

#include "Window.h"
#include "Input.h"
#include "Scene.h"
#include <string>
#include "Utils.h"

namespace slge
{
	class Window;
	class Input;

	class App : private Uncopyable
	{
		public:
			App( const std::string& name, unsigned width, unsigned height );
			~App();

			void run();
			void set( Scene* scene );

			static std::string getFPS();
			static double getGameSpeed();
	
		private:
			Window window;
			Input input;
			std::unique_ptr<Scene> scene;
	};

	inline void App::set( Scene* s )
	{
		scene.reset( s );
		s->loadGameEntities();
	}
};
#endif
