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
				background( ImageRef("Test.png") ),
				splash( background ),
				bgPos( CENTER_X, CENTER_Y ),
				newGame( Label( proggyTexter, "A N A T H A N E M", WINDOW_CENTER, Color::orange ), 10.f )
		{
			add( new Player() );
			add( new Wall( 0.f, 101.f, WINDOW_WIDTH, 101.f ) );
			add( new Wall( 0.f, 0.f, 0.f, WINDOW_HEIGHT ) );
			add( new Wall( WINDOW_WIDTH - 0.5f, 0.f, WINDOW_WIDTH - 0.5f, WINDOW_HEIGHT ) );
			add( new Wall( 0.f, 539.f, WINDOW_WIDTH, 539.f ) );
		}

	private:
		void doLoadGameEntities()
		{
		}

		void doUpdate()
		{
			if( newGame.update() ) printf( "CLICKED.\n" );
		}

		void doDraw()
		{
			glPushMatrix();
			glTranslatef( bgPos.getX(), bgPos.getY(), 0.f );
			splash.draw();
			glPopMatrix();
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
