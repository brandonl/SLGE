#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Box2D.h>
#include "Settings.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "Entity.h"
#include "SpatialComponent.h"
#include "PhysicsComponent.h"
#include "Window.h"
#include "Input.h"
#include <glm/glm.hpp>

class Player : public slge::Entity
{
	public:
		Player()
			:	slge::Entity( "Player" ),
				playerTexture( slge::ImageRef( "ITSP.png" ) ),
				sprite( playerTexture ),
				spatial( static_cast<float>( CENTER_X ), static_cast<float>( CENTER_Y ) )
		{
				//sprite.add( "Stand", 0, 0, 0, 0.0f );
				//sprite.add( "Run", 0, 3, 0, 12.0f );
				//sprite.add( "Jump", 0, 0, 1, 0.0f );
				//sprite.play( "Run" );
		}

	private:
		void doLoad()
		{
				b2BodyDef bDef;
				bDef.type = b2_dynamicBody;
				bDef.userData = this;
				bDef.allowSleep = false;
				bDef.position.Set(	spatial.getX() / slge::PTM_RATIO,
											spatial.getY() / slge::PTM_RATIO );
				bDef.angle = 0;
				physicalBody = slge::PhysicsComponent( bDef, &spatial );
			
				b2FixtureDef fixtureDef;
				b2PolygonShape actorBox;

				actorBox.SetAsBox( ( sprite.getHWidth() ) / slge::PTM_RATIO, 
											sprite.getHHeight() / slge::PTM_RATIO );
				fixtureDef.shape = &actorBox;
				fixtureDef.density = 1.0f;
				fixtureDef.restitution = 0.f;

				physicalBody.getBody()->CreateFixture( &fixtureDef );
				physicalBody.getBody()->SetFixedRotation(true);
		}

		void doUpdate()
		{
			sprite.update();
			physicalBody.update();

			b2Vec2 vel = body()->GetLinearVelocity();
			float bodyAngle = body()->GetAngle();
			float desiredAngle = 15.f;
         float change = 1 * slge::DEG2RAD;

			if( slge::Input::isKeyHeld( slge::Input::UP ) && vel.y >= -10.f )
			{
				if( bodyAngle <= desiredAngle * slge::DEG2RAD )
					body()->SetTransform( body()->GetPosition(), bodyAngle + change );
				body()->ApplyForce( b2Vec2(0,-200), body()->GetWorldCenter() );
			}
			else
			{
				if( bodyAngle > 0.001f )
					body()->SetTransform( body()->GetPosition(), bodyAngle - change );
			}
			body()->SetLinearVelocity( b2Vec2( 0.f, vel.y ) );
		}

		void doDraw() const
		{
			glPushMatrix();
			glTranslatef( spatial.getX(), spatial.getY(), 0.f );
			glRotatef( spatial.getAngle(), 0.f, 0.f, 1.f );
			//glScalef();
			sprite.draw();
			glPopMatrix();
		}

	private:
		b2Body *body()
		{ return physicalBody.getBody(); }

		slge::Texture2 playerTexture;
		slge::AnimatedSprite sprite;
		slge::SpatialComponent spatial;
		slge::PhysicsComponent physicalBody;
};

#endif