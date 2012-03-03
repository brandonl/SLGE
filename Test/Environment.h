#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <Box2D.h>
#include "Settings.h"
#include "Entity.h"
#include "SpatialComponent.h"
#include "PhysicsComponent.h"
#include "Vertex.h"
#include <algorithm>

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

class Terrain : public slge::Entity
{
	public:
		Terrain( int len, float theta, float step )
			:	Entity( "Terrain" ),
				length(len),
				angle(theta),
				step(step),
				currIndex(0),
				hasGameStarted(false)
		{
			currPos = glm::vec2( slge::Window::getWidth() + 5, 101.f );
		}

	private:
		void doLoad()
		{
			std::vector< b2Vec2 > terrainBuffer;
			for( size_t ix = 0; ix < slge::Window::getWidth(); ix += step )
			{
				terrainBuffer.push_back( b2Vec2	( ix / slge::PTM_RATIO, 
															( length * sin( ix * slge::DEG2RAD ) + 539.f ) / slge::PTM_RATIO ) );

			}
			b2BodyDef terrainBody;
			b2FixtureDef terrainFixture;

			terrainBody.position.Set( 0, 0 );
			terrainBody.userData = this;
			b2ChainShape polyChain;
			polyChain.CreateChain( &terrainBuffer[0], terrainBuffer.size() );
			terrainFixture.shape = &polyChain;
			terrainComponent1 = slge::PhysicsComponent( terrainBody );
			terrainComponent1.getBody()->CreateFixture( &terrainFixture );
			terrainComponent2 = slge::PhysicsComponent( terrainBody );
			terrainComponent2.getBody()->CreateFixture( &terrainFixture );
		}

		void doDraw() const 
		{
		}

		void doUpdate() 
		{
			if( slge::Input::isKeyPressed( slge::Input::UP ) )
				hasGameStarted = true;

			//if( hasGameStarted )
			//{
			//	//Start generating terrain
			//	//if( currIndex != curve.size() )// currIndex = 0;
			//	//{
			//	//	curve[ currIndex++ ] = slge::Vertex( currPos.x, currPos.y, 1.f, 1.f, slge::Color::orange );

			//	//	printf( "Pos: %f, %f.\n", currPos.x, currPos.y );
			//	//	currPos.x -= step;
			//	//	currPos.y = length * sin( currPos.x * slge::DEG2RAD );
			//	//	++currUsage;
			//	//}
			//}
		}

	private:
		int length;
		float angle;
		float step;
		size_t currUsage;
		size_t maxSize;
		size_t currIndex;
		bool hasGameStarted;
		glm::vec2 currPos;
		slge::PhysicsComponent terrainComponent1;
		slge::PhysicsComponent terrainComponent2;
};

#endif