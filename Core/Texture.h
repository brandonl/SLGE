#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <windows.h>
#include <gl/gl.h>
#include "Utils.h"

namespace slge
{
	class ImageRef;

	class Texture : private Uncopyable
	{
		public:
			~Texture();

			bool load( const ImageRef &iref );

			void bind() const;
			void unbind() const;

			const int		getWidth() const;
			const int		getHeight() const;
			const GLuint	getId() const;

		private:
			GLuint name;
			int width;
			int height;
	};

	inline void Texture::bind() const
	{
		glEnable( GL_TEXTURE_2D );//Not needed with shaders GL driver will tell GPU
		glBindTexture( GL_TEXTURE_2D, name );
	}

	inline void Texture::unbind() const
	{
		glDisable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	inline const int Texture::getWidth() const
	{
		return width;
	}

	inline const int Texture::getHeight() const
	{
		return height;
	}

	inline const GLuint Texture::getId() const
	{
		return name;
	}
};


#endif
