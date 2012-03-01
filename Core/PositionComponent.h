#ifndef __POSITION_COMPONENT_H__
#define __POSITION_COMPONENT_H__

#include <glm/glm.hpp>

//TODO: Make entity comp system; abstract component
class PositionComponent
{
	public:
		PositionComponent( float x, float y )
			: position( x, y )
		{}

		glm::vec2 position;
};

#endif