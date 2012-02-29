#ifndef __TEXT_2D_H__
#define __TEXT_2D_H__

#include <string>
#include <windows.h>
#include <gl/gl.h>
#include "Utils.h"
#include <array>
#include "Vertex.h"
#include "FontRef.h"

namespace slge
{
	class Text2 : private Uncopyable
	{
		public:
			explicit Text2( const FontRef &fref );
			~Text2();

			void bind() const;
			void unbind() const;
			void dynamicDrawString( const std::string& msg, float scale = 1.f ) const;
			const GLuint getId() const;
			
		private:
			void precomputeFontFaces( const FontRef &fref );

		private:
			GLuint name;
			std::array< std::array< Vertex, 4 >, 95 > precomputedSpatialGlyphs;
	};

	inline void Text2::bind() const
	{
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, name );
	}

	inline void Text2::unbind() const
	{
		glDisable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	inline const GLuint Text2::getId() const
	{
		return name;
	}
};

#endif