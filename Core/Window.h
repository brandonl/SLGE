#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "Utils.h"

namespace slge
{
	class Window : private Uncopyable
	{
		public:
			Window();
			~Window();
			void init( const std::string& , int, int, int, int );

			static void		update();
			static void		clear();
			static void		swapBuffers();
			static bool		isOpen();
			static int		getWidth();
			static int		getHeight();
			static float	getAspectRatio();
			static double	tick();
			static void		setTitle( const std::string& );

		private:
			static Window *instance;
			static void windowResize( int width, int height );
			static void	center();
			static int *displaySize();

		private:
			std::string title;
			int width;
			int height;
			int cdepth;
			int zbdepth;
			float ratio;
	};

};
#endif
