#include "vertex.h"

using namespace slge;

// Make sure Vertex size is a multiple of 32
static_assert( sizeof( slge::vertex ) % 32 == 0, "Vertex data does not fit on mutliple of 32 bit slot" );

vertex::vertex()
{
	memset( position, 0.0f, sizeof(GLfloat) * 2 );
	memset( texcoord, 0.0f, sizeof(GLfloat) * 2 );
	memset( vcolor, 0.0f, sizeof(GLfloat) * 4 );
}

vertex::vertex( float x, float y, float u, float v, const color& col )
{
	position[0] = x;
	position[1] = y;
	vcolor[0] = col.r;
	vcolor[1] = col.g;
	vcolor[2] = col.b;
	vcolor[3] = col.a;
	texcoord[0] = u;
	texcoord[1] = v;
}