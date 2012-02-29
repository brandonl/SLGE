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
	//float miny = 80000.0f, maxy = 0.0f;
	//		miny = gdata.y0 < miny ? gdata.y0 : miny;
	//		maxy = gdata.y1 > maxy ? gdata.y1 : maxy;
	//	}
	//}
	//aabb = Rect( 0.0f, miny, x, maxy + ( miny > 0.0f ? miny : miny * -1.0f ) );

	vertices = textBuilder.buildStaticString( text, center, col, size );
	//std::for_each( vertices.begin(), vertices.end(), 
	//					[&center]( Vertex &v )
	//					{ 
	//						printf( "Procesing.." ); 
	//						v.position[0] *= center.x;
	//						v.position[1] *= center.y;
	//					}
	//				);
}

Label::~Label()
{
}

void Label::draw() const
{
	glEnable( GL_BLEND );
	textBuilder.bind();
	glPushMatrix();
	glTranslatef( 50.f, 50.f, 0.0f );

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