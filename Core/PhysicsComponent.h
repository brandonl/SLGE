#ifndef __PHYSICS_COMPONENT_H__
#define __PHYSICS_COMPONENT_H__

#include <Box2D.h>
#include "Settings.h"
#include "SpatialComponent.h"

//TODO: This is temporary hack of class.
namespace slge
{
	class PhysicsComponent
	{
		public:
			PhysicsComponent()
				:	body(nullptr),
					sp(nullptr)
			{}

			PhysicsComponent( const b2BodyDef &bodyDef, SpatialComponent *sp = nullptr )
				:	body( static_cast<Entity*>( bodyDef.userData )->getParent()->createBody( bodyDef ) ),
					sp(sp)
			{
			}

			void update()
			{
				if( body && sp )
				{
					sp->setX( getXPosWorld() );
					sp->setY( getYPosWorld() );
				}
			}

			void changeVelocity( float x, float y );

			b2Body* getBody() const
			{
				return body;
			}

		private:
			const float getXPosWorld() const
			{
				return body->GetPosition().x * PTM_RATIO;
			}

			const float getYPosWorld() const
			{
				return body->GetPosition().y * PTM_RATIO;
			}

		private:
			b2Body *body;
			SpatialComponent *sp;
	};
};

#endif