#include "Vertex.h"
#include <algorithm>

using namespace slge;

static_assert( sizeof( slge::Vertex ) % 32 == 0, "Vertex data does not fit on mutliple of 32 bit slot" );

Vertex::Vertex()
{
	position.fill( 0.f );
	texCoord.fill( 0.f );
	vColor.fill( 0.0f );
}

Vertex::Vertex( float x, float y, float u, float v, const Color& col )
{
	position[0] = x;
	position[1] = y;
	vColor[0] = col.r;
	vColor[1] = col.g;
	vColor[2] = col.b;
	vColor[3] = col.a;
	texCoord[0] = u;
	texCoord[1] = v;
}
