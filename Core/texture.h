#ifndef TEXTURE_H
#define TEXTURE_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "resource.h"
#include <string>
#include <windows.h>
#include <gl/gl.h>

namespace slge
{

	class texture : public resource
	{
		public:
			explicit texture();
			~texture();

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

			int get_width() const
			{
				return width;
			}

			int get_height() const
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
