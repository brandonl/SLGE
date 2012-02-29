#ifndef __TEXT_2D_H__
#define __TEXT_2D_H__

#include <string>
#include <windows.h>
#include <gl/gl.h>
#include "Utils.h"
#include "Vertex.h"
#include "FontRef.h"
#include <glm/glm.hpp>
#include <vector>
#include "Color.h"

namespace slge
{
	class Text2 : private Uncopyable
	{
		public:
			explicit Text2( const FontRef &&fref );
			~Text2();

			const std::vector<Vertex> buildStaticString( const std::string& msg, glm::vec2 pos, const Color& col = Color(), float size = 0.f ) const;
			void immediateDrawString( const std::string& msg, glm::vec2 pos, const Color& col = Color(), float size = 0.f ) const;
			void bind() const;
			void unbind() const;
			const GLuint getId() const;

		private:
			const FontRef fref;
			GLuint name;
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