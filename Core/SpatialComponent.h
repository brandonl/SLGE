#ifndef __SPATIAL_COMPONENT_H__
#define __SPATIAL_COMPONENT_H__

#include <glm/glm.hpp>

namespace slge
{
	class SpatialComponent
	{
		public:
			SpatialComponent( float x = 0.f, float y = 0.f )
				:	position( x, y )
			{}

			void setX( float x )
			{
				position.x = x;
			}

			void setY( float y )
			{
				position.y = y;
			}

			const float getX() const
			{
				return position.x;
			}

			const float getY() const
			{
				return position.y;
			}

		private:
			glm::vec2 position;
	};
};

#endif