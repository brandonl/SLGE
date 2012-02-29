#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "Utils.h"

namespace slge
{
	class Window : private Uncopyable
	{
		friend class App;

		private:
			explicit Window( const std::string& , int, int, int, int );
			~Window();

			void update();
			void clear();
			void swapBuffers();
			bool isOpen();
			void close();
			void center();
			static void		windowResizeCB( int width, int height );

		public:
			static void				setTitle( const std::string& );
			static const float	getAspectRatio();
			static const int		getWidth();
			static const int		getHeight();
			static const int		getDisplayWidth();
			static const int		getDisplayHeight();
			static const double	tick();
	};

};
#endif
