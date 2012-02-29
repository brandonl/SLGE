#ifndef __TEXTURE_2D_H__
#define __TEXTURE_2D_H__

#include <string>
#include <windows.h>
#include <gl/gl.h>
#include "Utils.h"
#include "ImageRef.h"

namespace slge
{
	class Texture2 : private Uncopyable
	{
		public:
			explicit Texture2( const ImageRef &iref );
			~Texture2();

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

	inline void Texture2::bind() const
	{
		//Not needed with shaders GL driver will tell GPU
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, name );
	}

	inline void Texture2::unbind() const
	{
		glDisable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	inline const int Texture2::getWidth() const
	{
		return width;
	}

	inline const int Texture2::getHeight() const
	{
		return height;
	}

	inline const GLuint Texture2::getId() const
	{
		return name;
	}
};


#endif
