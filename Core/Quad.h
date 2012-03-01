#ifndef  __QUAD_H__
#define __QUAD_H__

#include <glm/glm.hpp>

namespace slge
{
	struct Quad
	{
		explicit Quad( glm::vec2 c = glm::vec2(1.f), float w = 0.f, float h = 0.f )
			:center(c), hwidth(w/2.f), hheight(h/2.f)
		{}

		glm::vec2 center;
		float hwidth;
		float hheight;
	};
};

#endif
