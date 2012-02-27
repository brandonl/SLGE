#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"
#include <string>
#include <windows.h>
#include <gl/gl.h>

namespace slge
{

	class Texture : public Resource
	{
		public:
			explicit Texture();
			~Texture();

			bool load( const std::string& fp, int w = -1, int h = -1 );

			void bind() const
			{
				glEnable( GL_TEXTURE_2D );
				glBindTexture( GL_TEXTURE_2D, name );
			}

			void unbind() const
			{
				glDisable( GL_TEXTURE_2D );
				glBindTexture( GL_TEXTURE_2D, 0 );
			}

			int getWidth() const
			{
				return width;
			}

			int getHeight() const
			{
				return height;
			}

		private:
			unsigned int name;
			int width;
			int height;
	};
};


#endif
