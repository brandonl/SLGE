#ifndef __SPATIAL_COMPONENT_H__
#define __SPATIAL_COMPONENT_H__

#include <glm/glm.hpp>

namespace slge
{
	class SpatialComponent
	{
		public:
			SpatialComponent( float x = 0.f, float y = 0.f, float theta = 0.f )
				:	position( x, y ),
					angle(theta)
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

			void setAngle( float theta )
			{
				angle = theta;
			}

			const float getAngle() const
			{
				return angle;
			}
		private:
			glm::vec2 position;
			float angle;
	};
};

#endif