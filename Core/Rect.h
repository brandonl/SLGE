#ifndef RECT_H
#define RECT_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

namespace slge
{
	struct Rect
	{
		Rect() {}
		Rect( float x, float y, float w, float h )
			: ux(x), uy(y), width(w), height(h)
		{}

		float ux, uy;
		float width;
		float height;
	};
};

#endif
