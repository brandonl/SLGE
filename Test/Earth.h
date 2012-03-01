#ifndef __TEST_H__
#define __TEST_H__

#include <functional>
#include <ctime>
#include <cstdio>
#include <Box2D.h>
#include <windows.h>
#include <gl/gl.h>
#include "Scene.h"
#include "Settings.h"
#include "Text2D.h"
#include "Texture2D.h"
#include "Label.h"
#include "Button.h"
#include "Sprite.h"
#include "Entity.h"
#include "PositionComponent.h"
#include <glm/glm.hpp>

using namespace slge;
using namespace glm;

#define CENTER_X Window::getWidth() >> 1
#define CENTER_Y Window::getHeight() >> 1
#define WINDOW_CENTER glm::vec2( CENTER_X, CENTER_Y )

static const float BEXTENT = 48.0f;
static const float PEXTENT = 32.0f;
static const float CEXTENT = 48.0f;

/*
class Wall : public Actor
{
	public:
		Wall( const glm::vec2& pos, const glm::vec2& pos2, std::function<b2Body*(const b2BodyDef&)> &&bodyMaker )
			: Actor( "Wall" )
		{
			b2EdgeShape edgeShape;
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &edgeShape;
			myFixtureDef.density = 1;
			b2BodyDef bd;
			bd.userData = this;
			bd.type = b2_staticBody;
			bd.angle = 0;
			bd.position.Set( pos.x / PTM_RATIO, pos.y / PTM_RATIO );
			edgeShape.Set(b2Vec2( pos.x / PTM_RATIO, pos.y / PTM_RATIO ),b2Vec2( pos2.x / PTM_RATIO, pos2.y / PTM_RATIO ) );
			body = bodyMaker(bd);
			body->CreateFixture(&myFixtureDef);
		}

		~Wall() { std::cout << "Destroying Wall... " << id << std::endl;}
		void draw() {}
		void update()
		{
		}
		void onCollission( Entity *collider ) {}
};
*/

class Player : public Entity
{
	public:
		Player()
			:	Entity("Player"),
				playerTexture( ImageRef( "Ogmo.png" ) ),
				sprite( playerTexture, 32, 32 ),
				position( CENTER_X, CENTER_Y )
		{
				sprite.add( "Stand", 0, 0, 0, 0.0f );
				sprite.add( "Run", 0, 3, 0, 12.0f );
				sprite.add( "Jump", 0, 0, 1, 0.0f );
				sprite.play( "Run" );
		}

	private:
		void doUpdate()
		{
			sprite.update();
		}

		void doDraw() const
		{
			glPushMatrix();
			glTranslatef( position.position.x, position.position.y, 0.f );
			sprite.draw();
			glPopMatrix();
		}

	private:
		Texture2 playerTexture;
		AnimatedSprite sprite;
		PositionComponent position;
};

class SplashScreen : public Scene
{
	public:
		SplashScreen()
			:	proggyTexter( FontRef( "ProggySquare.ttf" ) ),
				background( ImageRef("Test.png") ),
				splash( background ),
				newGame( Label( proggyTexter, "THE MOON IS A HARSHH", WINDOW_CENTER, Color::orange ), 10.f )
		{
			add( new Player() );
		}

	private:
		void doUpdate()
		{
			if( newGame.update() ) printf( "CLICKED.\n" );
		}

		void doDraw()
		{
			splash.draw();
			proggyTexter.immediateDrawString( "rom", vec2( 1.f, 11.f ) );
			newGame.draw();
		}

	private:
		// Assets, self manage creation and duplication
		// TODO: Add Asset flyweight so user cant simply pass strings to
		// objects such as sprites and not worry about recreating same asset (texture, sound, font)
		Text2 proggyTexter;
		Texture2 background;

		StaticSprite splash;
		Button<Label> newGame;
};

#endif
