#ifndef VERTEX_H
#define VERTEX_H

#include <windows.h>
#include <gl/gl.h>
#include "Color.h"
#include <array>
#include <vector>

namespace slge
{
	struct Vertex
	{
		Vertex();
		explicit Vertex( float x, float y, float u, float v, const Color& col = Color() );

		std::array<GLfloat, 2> position;
		std::array<GLfloat, 2> texCoord;
		std::array<GLfloat, 4> vColor;
	};
	typedef std::vector<Vertex> VertList;
};
#endif
