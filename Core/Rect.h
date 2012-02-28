#ifndef RECT_H
#define RECT_H

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
