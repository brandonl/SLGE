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
		Terrain( int len, float theta, float step, float yPos )
			:	Entity( "Terrain" ),
				length(len),
				angle(theta),
				step(step),
				yPos( yPos ),
				hasGameStarted(false),
				physicsVel( 50.f * slge::DELTA_TIMEF )
		{
		}

	private:
		void doLoad()
		{
			std::vector< b2Vec2 > terrainBuffer1;
			std::vector< b2Vec2 > terrainBuffer2;
			for( size_t ix = 0, jx = slge::Window::getWidth(); ix <= slge::Window::getWidth(); ix += step, jx += step )
			{
				// Terrain 1 Buffers's cetneroid is 0,0
				terrainBuffer1.push_back( b2Vec2	( ix / slge::PTM_RATIO, 
															length * sin( ix * slge::DEG2RAD )  / slge::PTM_RATIO ) );
				// Whereas Terrain 2 Buffer is centered at WindowWidth, 0, Since we want the terrain generation
				// to match up we supply T2 with the same x values as T1 offset by window window since that's its center.
				// It's y values however are calculated as if x were starting at WindowWidth.
				terrainBuffer2.push_back( b2Vec2	( ix / slge::PTM_RATIO, 
															length * sin( jx * slge::DEG2RAD ) / slge::PTM_RATIO ) );

			}
			b2BodyDef terrainBody;
			b2FixtureDef terrainFixture;

			terrainBody.position.Set( 0.f, yPos / slge::PTM_RATIO );
			terrainBody.userData = this;
			b2ChainShape polyChain1;
			polyChain1.CreateChain( &terrainBuffer1[0], terrainBuffer1.size() );
			terrainFixture.shape = &polyChain1;
			leftTerrain.reset( new slge::PhysicsComponent( terrainBody ) );
			leftTerrain->getBody()->CreateFixture( &terrainFixture );

			terrainBody.position.Set( slge::Window::getWidth() / slge::PTM_RATIO, yPos / slge::PTM_RATIO );
			b2ChainShape polyChain2;
			polyChain2.CreateChain( &terrainBuffer2[0], terrainBuffer2.size() );
			terrainFixture.shape = &polyChain2;
			rightTerrain.reset( new slge::PhysicsComponent( terrainBody ) );
			rightTerrain->getBody()->CreateFixture( &terrainFixture );
		}

		void doDraw() const 
		{
			b2ChainShape *chain = static_cast<b2ChainShape*>( leftTerrain->getBody()->GetFixtureList()->GetShape() );
			unsigned count = chain->m_count;
			const b2Vec2 *verts = chain->m_vertices;
			b2Vec2 v1 = b2Mul( leftTerrain->getBody()->GetTransform(), verts[0] );
			float yDraw = static_cast<float>( slge::Window::getHeight() );
			if( yPos <= CENTER_Y )
				yDraw = 0.f;
			glColor4f( 0.58f, .41f, .20f, 1.0f );
			for( unsigned i = 1; i < count; ++i )
			{
				glBegin( GL_QUADS );
				b2Vec2 v2 = b2Mul( leftTerrain->getBody()->GetTransform(), verts[i] );
				glVertex2f( v1.x * slge::PTM_RATIO, yDraw );
				glVertex2f( v1.x * slge::PTM_RATIO, v1.y * slge::PTM_RATIO );
				glVertex2f( v2.x * slge::PTM_RATIO, v2.y * slge::PTM_RATIO );
				glVertex2f( v2.x * slge::PTM_RATIO, yDraw );
				glEnd();
				v1 = v2;
			}

			chain = static_cast<b2ChainShape*>( rightTerrain->getBody()->GetFixtureList()->GetShape() );
			count = chain->m_count;
			verts = chain->m_vertices;
			v1 = b2Mul( rightTerrain->getBody()->GetTransform(), verts[0] );
			glColor4f( 0.58f, .41f, .20f, 1.0f );
			for( unsigned i = 1; i < count; ++i )
			{
				glBegin( GL_QUADS );
				b2Vec2 v2 = b2Mul( rightTerrain->getBody()->GetTransform(), verts[i] );
				glVertex2f( v1.x * slge::PTM_RATIO, yDraw );
				glVertex2f( v1.x * slge::PTM_RATIO, v1.y * slge::PTM_RATIO );
				glVertex2f( v2.x * slge::PTM_RATIO, v2.y * slge::PTM_RATIO );
				glVertex2f( v2.x * slge::PTM_RATIO, yDraw );
				glEnd();
				v1 = v2;
			}
			glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		}

		void generateTerrain()
		{
			leftTerrain->getBody()->SetTransform( b2Vec2( slge::Window::getWidth() / slge::PTM_RATIO, leftTerrain->getBody()->GetWorldCenter().y ), 
																		leftTerrain->getBody()->GetAngle() );

			std::vector< b2Vec2 > terrainBuffer;
			terrainBuffer.reserve( slge::Window::getWidth() / step );
			for( size_t ix = 0, jx = slge::Window::getWidth() * 2.f; ix <= slge::Window::getWidth(); ix += step, jx += step )
				terrainBuffer.push_back( b2Vec2( ix / slge::PTM_RATIO, 
															length * sin( jx * slge::DEG2RAD )  / slge::PTM_RATIO ) );

			b2FixtureDef terrainFixture;
			b2ChainShape polyChain1;

			polyChain1.CreateChain( &terrainBuffer[0], terrainBuffer.size() );
			terrainFixture.shape = &polyChain1;
			// This thing better have only 1 Fixture.
			b2Fixture *fix = leftTerrain->getBody()->GetFixtureList();
			leftTerrain->getBody()->DestroyFixture( fix );
			leftTerrain->getBody()->CreateFixture( &terrainFixture );
		}

		void doUpdate() 
		{
			b2Vec2 leftPos = leftTerrain->getBody()->GetWorldCenter();
			b2Vec2 rightPos = rightTerrain->getBody()->GetWorldCenter();

			leftTerrain->getBody()->SetTransform( b2Vec2( ( (	leftPos.x * slge::PTM_RATIO ) - physicsVel ) / slge::PTM_RATIO, leftPos.y ), 
						  														leftTerrain->getBody()->GetAngle() );
			rightTerrain->getBody()->SetTransform( b2Vec2( ( ( rightPos.x * slge::PTM_RATIO ) - physicsVel ) / slge::PTM_RATIO, rightPos.y ), 
																				rightTerrain->getBody()->GetAngle() );

			// Once rightTerrains's point is 1 step form 0 re generate new terrain for leftTerrain starting at WindowsWidth
			if( rightPos.x * slge::PTM_RATIO <= 0.f )
			{
				// Generates terrain for the current leftTerrain moves it to the right
				generateTerrain();
				std::swap( leftTerrain, rightTerrain );
			}

			if( slge::Input::isKeyHeld( slge::Input::UP ) )
			{
				// Begin random terrain generation no more sinewave
				hasGameStarted = true;
			}
		}

	private:
		int length;
		float angle;
		float step;
		float yPos;
		bool hasGameStarted;
		float physicsVel;
		std::unique_ptr< slge::PhysicsComponent > rightTerrain;
		std::unique_ptr< slge::PhysicsComponent > leftTerrain;
};

#endif