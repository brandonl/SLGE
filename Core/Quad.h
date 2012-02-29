#ifndef  __QUAD_H__
#define __QUAD_H__

#include <glm/glm.hpp>

namespace slge
{
	struct Quad
	{
		explicit Quad( glm::vec2 c = glm::vec2(1.f), float w = 0.f, float h = 0.f )
			:center(c), width(w), height(h)
		{}

		glm::vec2 center;
		float width;
		float height;
	};
};

#endif
