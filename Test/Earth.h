#ifndef __TEST_H__
#define __TEST_H__

#include <cstdio>
#include <windows.h>
#include <gl/gl.h>
#include "Scene.h"
#include "Settings.h"
#include "Text2D.h"
#include "Label.h"
#include "Button.h"
#include <glm/glm.hpp>
#include "Player.h"
#include "Environment.h"

using namespace slge;
using namespace glm;


class SplashScreen : public Scene
{
	public:
		SplashScreen()
			:	proggyTexter( FontRef( "ProggySquare.ttf" ) ),
				background( ImageRef("bg.png") ),
				splash( background ),
				bgPos( CENTER_X, CENTER_Y ),
				newGame( Label( proggyTexter, "PRESS - UP : PRESS - DOWN", glm::vec2( CENTER_X, 10.f ), Color::orange ), 10.f )
		{
			add( new Player() );
			add( new Terrain( 50, 45.f, 20.f, 100.f ) );
			add( new Terrain( 50, 45.f, 20.f, 700.f ) );
		}

	private:
		void doLoadGameEntities()
		{
		}

		void doUpdate()
		{
			if( newGame.update() ) printf( "CLICKED.\n" );
		}

		void preDraw()
		{
			//Create spatial component get rid of gl calls.
			glPushMatrix();
			glTranslatef( bgPos.getX(), bgPos.getY(), 0.f );
			splash.draw();
			glPopMatrix();
		}

		void postDraw()
		{
			proggyTexter.immediateDrawString( "FPS: " + App::getFPS(), vec2( 1.f, 11.f ) );
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
		SpatialComponent bgPos;
};

#endif
