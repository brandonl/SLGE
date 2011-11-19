#ifndef VERTEX_H
#define VERTEX_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <windows.h>
#include <gl/gl.h>
#include "color.h"

namespace slge
{
	struct vertex
	{
		explicit vertex();
		explicit vertex( float x, float y, float u, float v, const color& col = color() );

		GLfloat position[2];
		GLfloat texcoord[2];
		GLfloat vcolor[4];
	};
};
#endif