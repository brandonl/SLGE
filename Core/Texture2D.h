#ifndef __TEXTURE_2D_H__
#define __TEXTURE_2D_H__

#include <string>
#include <windows.h>
#include <gl/gl.h>
#include "ImageRef.h"
#include "Utils.h"

namespace slge
{
	class Texture2 : public Uncopyable
	{
		public:
			explicit Texture2( const ImageRef &&iref );
			explicit Texture2( const std::string &imageFileName );
			~Texture2();

			void bind() const;
			void unbind() const;

			const int		getHWidth() const;
			const int		getHHeight() const;
			const GLuint	getId() const;

		private:
			GLuint name;
			int hwidth;
			int hheight;
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

	inline const int Texture2::getHWidth() const
	{
		return hwidth;
	}

	inline const int Texture2::getHHeight() const
	{
		return hheight;
	}

	inline const GLuint Texture2::getId() const
	{
		return name;
	}
};


#endif
