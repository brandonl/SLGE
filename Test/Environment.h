#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <Box2D.h>
#include "Settings.h"
#include "Entity.h"
#include "SpatialComponent.h"
#include "PhysicsComponent.h"


class Wall : public slge::Entity
{
	public:
		Wall( float ulx, float uly, float lrx, float lry ) 
			:	slge::Entity( "Wall" ),
				leftPos( ulx, uly ),
				rightPos( lrx, lry )
		{
		}

	private:
		void doLoad()
		{
			b2EdgeShape edgeShape;
			myFixtureDef.shape = &edgeShape;
			myFixtureDef.density = 1;
			bd.userData = this;
			bd.type = b2_staticBody;
			bd.angle = 0;
			bd.position.Set( 0.f, 0.f );

			//Positions are in relation to bodys center of gravity 0,0
			edgeShape.Set(	b2Vec2(	leftPos.getX() / slge::PTM_RATIO, 
											leftPos.getY() / slge::PTM_RATIO ),
								b2Vec2(	rightPos.getX() / slge::PTM_RATIO, 
											rightPos.getY() / slge::PTM_RATIO ) 
							 );
			physicalBody = slge::PhysicsComponent( bd );
			physicalBody.getBody()->CreateFixture(&myFixtureDef);
		}

		void doDraw() const {}
		void doUpdate() {}

	private:
		b2BodyDef bd;
		b2FixtureDef myFixtureDef;
		slge::SpatialComponent leftPos;
		slge::SpatialComponent rightPos;
		slge::PhysicsComponent physicalBody;
};
#endif