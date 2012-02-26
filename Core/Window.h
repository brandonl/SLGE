#ifndef WINDOW_H
#define WINDOW_H

#include <string>

namespace slge
{
	class Window
	{
		public:
			explicit Window();
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
			static void		center();
			static int		*displaySize();

		private:
			std::string title;
			int width;
			int height;
			int cdepth;
			int zbdepth;
			float ratio;

			static Window *instance;
			static void keyEventCallback( int, int );
			static void mouseButtonCallback( int, int );
			static void mousePositionCallBack( int, int );
	};

};
#endif
