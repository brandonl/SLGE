#include "Label.h"
#include <windows.h>
#include <gl/gl.h>
#include "Text2D.h"
#include <algorithm>
#include <functional>

using namespace slge;

Label::Label( const Text2 &textBuilder, const std::string &text, const glm::vec2& center, const Color& col, float size )
	:	textBuilder(textBuilder),
		text(text),
		bounds(center)
{
	vertices = textBuilder.buildStaticString( text, center, col, size );
	//	Centering:This position is gaurenteed the largest x,y based on Tex2D creation.
	// Not safe if things change; switch to std::max_element.
	bounds.hwidth = ( ( vertices.end() - 2 )->position[0] - center.x ) / 2.f;
	bounds.hheight = ( ( vertices.end() - 2 )->position[1] - center.y ) / 2.f;

	std::for_each(	vertices.begin(), vertices.end(), 
						[=]( Vertex &v ){ v.position[0] += -bounds.hwidth; v.position[1] += -bounds.hheight; } );
}

Label::~Label()
{
}

void Label::draw() const
{
	glEnable( GL_BLEND );
	textBuilder.bind();
	glPushMatrix();

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer( 2, GL_FLOAT, sizeof(Vertex), &vertices[0].position );
		glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &vertices[0].texCoord );
		glColorPointer( 4, GL_FLOAT, sizeof(Vertex), &vertices[0].vColor );
		glDrawArrays( GL_QUADS, 0, vertices.size() );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
	textBuilder.unbind();
	glDisable( GL_BLEND );
}