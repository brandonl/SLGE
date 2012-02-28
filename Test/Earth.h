#ifndef TEST_H
#define TEST_H

#include "Scene.h"
#include "World.h"
#include "Window.h"
#include <Box2D.h>
#include <ctime>
#include "Resourcemodule.h"
#include "Defines.h"
#include <functional>

using namespace slge;

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

#include "ImageRef.h"

class home : public Scene
{
	public:
		home()
			:	ref( ImageRef( "Bcomet.tga" ) )
		{
		}

		~home()  {}

	private:
		void doInit()
		{
			//leftBound = new Wall( glm::vec2( 0, 0 ), glm::vec2( 0, Window::getHeight() ), std::bind( &Scene::createBody, this, std::placeholders::_1 ) );
			//title = Label( "THE MOON ISA", Resources::grabFont( "ProggySquare.ttf", 36.0f ), glm::vec2( Window::getWidth() >> 1, 25.0f ),  Color::purple );
		}

		void doUpdate()
		{
		}

		void doDraw()
		{
			Scene::doDraw();
			//title.draw();
		}

	private:
		ImageRef ref;
		//Label title;
		//Wall *leftBound;
};

#endif
