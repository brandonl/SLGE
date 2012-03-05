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
				spatial( static_cast<float>( CENTER_X ), static_cast<float>( CENTER_Y ) ),
				runTime( 0.f ),
				balanced(true),
				desiredAngle(10.f),
				upChange(0.5f * slge::DEG2RAD),
				downChange(-0.5f * slge::DEG2RAD),
				wobbleChange(0.2f * slge::DEG2RAD),
				yVel( -120.f ),
				gameStarted(false)
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
				bDef.allowSleep = true;
				bDef.awake = false;
			//	spatial.setY( spatial.getY()  );
				bDef.position.Set(	spatial.getX() / slge::PTM_RATIO,
											spatial.getY() / slge::PTM_RATIO );
				bDef.angle = 0;
				physicalBody = slge::PhysicsComponent( bDef, &spatial );
			
				b2FixtureDef fixtureDef;
				b2PolygonShape actorShape;
				b2Vec2 verts[] = { b2Vec2( (sprite.getHWidth()) / slge::PTM_RATIO,
													(sprite.getHHeight() - 12) / slge::PTM_RATIO 
												),
												
										b2Vec2( -(sprite.getHWidth()) / slge::PTM_RATIO,
													(sprite.getHHeight() - 12) / slge::PTM_RATIO 
												),
										b2Vec2( 0.f, ( -sprite.getHHeight() + 12) / slge::PTM_RATIO )
										};
				actorShape.Set( verts, 3 );
				fixtureDef.shape = &actorShape;
				fixtureDef.density = 1.0f;
				fixtureDef.restitution = 0.f;

				// Change linear Dampaning as a perk allows you to be more floaty
				// or change gravity on the body...
				//physicalBody.getBody()->SetLinearDamping( 1.f );
				//physicalBody.getBody()->SetGravityScale( 0.5f );

				body()->CreateFixture( &fixtureDef );
				body()->SetFixedRotation(true);
		}

		void doUpdate()
		{
			if( gameStarted )
			{
				sprite.update();
				physicalBody.update();

				b2Vec2 vel = body()->GetLinearVelocity();
				float bodyAngle = body()->GetAngle();

				if( slge::Input::isKeyHeld( slge::Input::UP ) )
				{
					if( bodyAngle < desiredAngle * slge::DEG2RAD )
						body()->SetTransform( body()->GetPosition(), bodyAngle + upChange );
					body()->ApplyForce( b2Vec2(0.f, yVel ), body()->GetWorldCenter() );
					balanced = false;
				}
				else if( slge::Input::isKeyHeld( slge::Input::DOWN ) )
				{
					if( bodyAngle > -desiredAngle * slge::DEG2RAD )
						body()->SetTransform( body()->GetPosition(), bodyAngle - upChange );
					body()->ApplyForce( b2Vec2(0.f, -yVel ), body()->GetWorldCenter() );
					balanced = false;
				}
				else
				{
					if( !balanced )
					{
						if( bodyAngle > 0.f )
							body()->SetTransform( body()->GetPosition(), bodyAngle + downChange );
						else
							balanced = true;
					}
					else
					{
						if( sin( runTime * slge::DEG2RAD ) < 0.f )
							body()->SetTransform( body()->GetPosition(), bodyAngle + wobbleChange );
						else
							body()->SetTransform( body()->GetPosition(), bodyAngle - wobbleChange );
					}
					runTime += 4.f;
				}
				body()->SetLinearVelocity( b2Vec2( 0.f, vel.y ) );
			}
			else
			{
				if( slge::Input::isKeyHeld( slge::Input::UP ) )
				{
					body()->SetAwake( true );
					gameStarted = true;
				}
			}
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
		float runTime;
		bool balanced;
		float desiredAngle;
		float upChange;
		float downChange;
		float wobbleChange;
		float yVel;
		bool gameStarted;
		slge::Texture2 playerTexture;
		slge::AnimatedSprite sprite;
		slge::SpatialComponent spatial;
		slge::PhysicsComponent physicalBody;
};

#endif