#include <iostream>
#include "label.h"
#include <windows.h>
#include <gl/gl.h>

using namespace slge;

label::label( const std::string &text, font *f, const b2Vec2& center, const color& col )
	:	text(text),
		center(center),
		typography(0)
{
	typography = f;

	// Build AABB based on where STB draws the font and the length it returns
	float x = 0.0f, y = 0.0f;
	float miny = 80000.0f, maxy = 0.0f;
	for( unsigned int i = 0; i < text.size(); ++i )
	{
		char c = text[i];
		if( c >= 32 && c < 128 )
		{
			font::glyph_data gdata = typography->get_glyph_data( c, &x, &y );
			vertices.push_back( vertex( gdata.x0, gdata.y0, gdata.s0, gdata.t0, col ) );
			vertices.push_back( vertex( gdata.x1, gdata.y0, gdata.s1, gdata.t0, col ) );
			vertices.push_back( vertex( gdata.x1, gdata.y1, gdata.s1, gdata.t1, col ) );
			vertices.push_back( vertex( gdata.x0, gdata.y1, gdata.s0, gdata.t1, col ) );
			miny = gdata.y0 < miny ? gdata.y0 : miny;
			maxy = gdata.y1 > maxy ? gdata.y1 : maxy;
		}
	}
	aabb = rect( 0.0f, miny, x, maxy + ( miny > 0.0f ? miny : miny * -1.0f ) );
}

label::~label()
{
}

void label::draw() const
{
	glEnable( GL_BLEND );
	typography->use();
	glPushMatrix();
	glTranslatef( center.x - aabb.width/2.0, center.y + aabb.height/2.0f, 0.0f );

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer( 2, GL_FLOAT, sizeof(vertex), &vertices[0].position );
		glTexCoordPointer( 2, GL_FLOAT, sizeof(vertex), &vertices[0].texcoord );
		glColorPointer( 4, GL_FLOAT, sizeof(vertex), &vertices[0].vcolor );
		glDrawArrays( GL_QUADS, 0, vertices.size() );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
	typography->toss();
	glDisable( GL_BLEND );
}
float label::get_width() const
{
	return aabb.width;
}

float label::get_height() const
{
	return aabb.height;
}
