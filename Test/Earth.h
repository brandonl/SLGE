#ifndef TEST_H
#define TEST_H

#include <functional>
#include <ctime>
#include <cstdio>
#include <Box2D.h>

static const float BEXTENT = 48.0f;
static const float PEXTENT = 32.0f;
static const float CEXTENT = 48.0f;

///////////////////////////////////////////////////////////////////////////////
// Title Screen
///////////////////////////////////////////////////////////////////////////////
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

#include "Scene.h"
#include "Settings.h"
#include "Text2D.h"
#include "Texture2D.h"

using namespace slge;

class Home : public Scene
{
	public:
		Home()
			:	label( FontRef( "arial.ttf" ) ),
				testTexture( ImageRef("Earthling.png") )
		{
		}

	private:

		void doUpdate()
		{
		}

		void doDraw()
		{
			Scene::doDraw();
			label.dynamicDrawString( "Random" );
			//title.draw();
		}

	private:
		Text2 label;
		Texture2 testTexture;
		//Label title;
		//Wall *leftBound;
};

#endif
