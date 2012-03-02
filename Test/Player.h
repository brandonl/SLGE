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
				playerTexture( slge::ImageRef( "Ogmo.png" ) ),
				sprite( playerTexture, 32, 32 ),
				position( static_cast<float>( CENTER_X ), static_cast<float>( CENTER_Y ) )
		{
				sprite.add( "Stand", 0, 0, 0, 0.0f );
				sprite.add( "Run", 0, 3, 0, 12.0f );
				sprite.add( "Jump", 0, 0, 1, 0.0f );
				sprite.play( "Run" );
		}

	private:
		void doLoad()
		{
				b2BodyDef bDef;
				bDef.type = b2_dynamicBody;
				bDef.userData = this;
				bDef.position.Set(	position.getX() / slge::PTM_RATIO,
											position.getY() / slge::PTM_RATIO );
				bDef.angle = 0;
				physicalBody = slge::PhysicsComponent( bDef, &position );
			
				b2FixtureDef fixtureDef;

				b2PolygonShape actorBox;
				actorBox.SetAsBox( ( sprite.getHWidth() - 6 ) / slge::PTM_RATIO, 
											sprite.getHWidth() / slge::PTM_RATIO );
				fixtureDef.shape = &actorBox;
				fixtureDef.density = 1.0f;
				fixtureDef.restitution = 0.f;

				physicalBody.getBody()->CreateFixture( &fixtureDef );
				//physicalBody.getBody()->SetFixedRotation(true);
				//physicalBody.getBody()->SetGravityScale( 8.0f );
				//actorBox.SetAsBox( ( sprite.getHWidth() - 8.1f ) / PTM_RATIO, 
				//							0.3f / PTM_RATIO, 
				//							b2Vec2( 0, ( sprite.getHWidth() - 0.3f) / PTM_RATIO ), 0 );
				// Create foot...
				//fixtureDef.friction = 1.0f;
				//b2Fixture* footSensorFixture = physicalBody.getBody()->CreateFixture(&fixtureDef);
				//Special case looked for in World...
				//footSensorFixture->SetUserData( (void*)FOOT );
		}

		void doUpdate()
		{
			sprite.update();
			physicalBody.update();

			b2Vec2 vel = body()->GetLinearVelocity();
			float bodyAngle = body()->GetAngle();

			if( slge::Input::isKeyHeld( slge::Input::UP ) && vel.y >= -18.f )
			{
            float totalRotation = 90.f - bodyAngle;
            while ( totalRotation < 180 * slge::DEG2RAD ) totalRotation += 360 * slge::DEG2RAD;
            while ( totalRotation > 180 * slge::DEG2RAD ) totalRotation -= 360 * slge::DEG2RAD;
            float change = 1 * slge::DEG2RAD; //allow 1 degree rotation per time step
            float newAngle = bodyAngle + b2Min( change, b2Max(-change, totalRotation));
            body()->SetTransform( body()->GetPosition(), newAngle );
            body()->SetAngularVelocity(0);
				//body()->SetTransform( b2Vec2( body()->Get, 0.f ), 50 * slge::DEG2RAD );
				//body()->SetAngularVelocity( 35 * slge::DEG2RAD );
				body()->ApplyForce( b2Vec2(0,-20), body()->GetWorldCenter() );
			}
			else
			{
				body()->SetAngularVelocity( slge::DEG2RAD );
			}
			body()->SetLinearVelocity( b2Vec2( 0.f, vel.y ) );
		}

		void doDraw() const
		{
			glPushMatrix();
			glTranslatef( position.getX(), position.getY(), 0.f );
			sprite.draw();
			glPopMatrix();
		}

	private:
		b2Body *body()
		{ return physicalBody.getBody(); }

		slge::Texture2 playerTexture;
		slge::AnimatedSprite sprite;
		slge::SpatialComponent position;
		slge::PhysicsComponent physicalBody;
};

#endif