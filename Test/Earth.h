#ifndef TEST_H
#define TEST_H

#include "Scene.h"
#include "World.h"
#include "Window.h"
#include <Box2D.h>
#include <ctime>
#include "Resourcemodule.h"
#include "Button.h"
#include "Label.h"
#include "Actor.h"
#include "Sprite.h"

using namespace slge;

static const float BEXTENT = 48.0f;
static const float PEXTENT = 32.0f;
static const float CEXTENT = 48.0f;

class GameOver : public Scene
{
	public:
		GameOver()
		{
			banner = Label( "GAME OVER", Resources::grabFont( "ProggySquare.ttf", 62.0f ), glm::vec2( Window::getWidth() >> 1, Window::getHeight() >> 1 ), Color() );
		}
		~GameOver() {	std::cout << "Destroying game over... " << std::endl;}

		void init()
		{
		}

		void update()
		{
		}

		void draw()
		{
			banner.draw();
		}

	private:
		Label banner;
};

//////////////////////////////////////////////////////////////////////////////
// Gameplay
//////////////////////////////////////////////////////////////////////////////
class player : public Actor
{
	public:
		explicit player() : Actor() {};
		explicit player( const glm::vec2& pos )
			:	Actor( "Player" ),
				inAir(true)
		{
			//graphic = std::auto_ptr<Sprite>( new Sprite( "Res/Ogmo.tga", 8, 8, 64, 32 ) );
			graphic = std::auto_ptr<Sprite>( new Sprite( "Ogmo2.tga", 32, 32, 256, 128 ) );
			graphic->add( "Stand", 0, 0, 0, 0.0f );
			graphic->add( "Run", 0, 3, 0, 12.0f );
			graphic->add( "Jump", 0, 0, 1, 0.0f );
			graphic->play( "Run" );

			//Actor Body
			{
				b2BodyDef actorBodyDef;
				actorBodyDef.type = b2_dynamicBody;
				actorBodyDef.userData = this;
				actorBodyDef.position.Set( pos.x / PTM_RATIO, pos.y / PTM_RATIO );
				actorBodyDef.angle = 0;
				body = World::get()->CreateBody( &actorBodyDef );
			}
			// Actor Shape
			{
				b2FixtureDef fixtureDef;

				b2PolygonShape actorBox;
				actorBox.SetAsBox( ( graphic->getHwidth() - 6 ) / PTM_RATIO, graphic->getHheight() / PTM_RATIO );
				fixtureDef.shape = &actorBox;
				fixtureDef.density = 1.0f;
				fixtureDef.friction = 0.0f;
				body->CreateFixture( &fixtureDef );
				body->SetFixedRotation(true);
				body->SetGravityScale( 8.0f );
				actorBox.SetAsBox( ( graphic->getHwidth() - 8.1f ) / PTM_RATIO, 0.3f / PTM_RATIO, b2Vec2( 0, ( graphic->getHheight() - 0.3f) / PTM_RATIO ), 0 );
				// Create foot...
				fixtureDef.friction = 1.0f;
				b2Fixture* footSensorFixture = body->CreateFixture(&fixtureDef);
				//Special case looked for in World...
				footSensorFixture->SetUserData( (void*)FOOT );
			}
		}

		~player() { std::cout << "Destroying player... " << id << std::endl;};

		void update()
		{
			Actor::update();
			if( Input::isKeyHeld( Input::LEFT ) )
			{
				body->SetAwake( true );
				float y = body->GetLinearVelocity().y;
				body->SetLinearVelocity(b2Vec2( -6.0f, y ) );
			}

			if( Input::isKeyHeld( Input::RIGHT ) )
			{
				body->SetAwake( true );
				float y = body->GetLinearVelocity().y;
				body->SetLinearVelocity(b2Vec2( 6.0f, y ) );
			}

			if( Input::isKeyPressed( Input::UP ) && !inAir )
			{
				inAir = true;
				body->SetAwake( true );
				float x = body->GetLinearVelocity().x;
				body->SetLinearVelocity(b2Vec2( x, -26.0f ) );
			}
		};

		void handleSpecial()
		{
			inAir = false;
		}

		void onCollission( Entity *collider )
		{
		};

		bool inAir;
};

class wall : public Actor
{
	public:
		explicit wall() : Actor() {};
		explicit wall( const glm::vec2& pos, const glm::vec2& pos2 )
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
			body = World::get()->CreateBody(&bd);
			body->CreateFixture(&myFixtureDef);
		}

		~wall() { std::cout << "Destroying wall... " << id << std::endl;};
		void draw() {};
		void update()
		{
		};
		void onCollission( Entity *collider ) {};
};

class block : public Actor
{
	public:

		explicit block() : Actor() {};
		explicit block( const glm::vec2& pos, int level )
			: Actor( "Ground" )
		{
			int randy = rand() % 3;
			Color ref;
			switch( level )
			{
				case 0:
					switch( randy )
					{
						case 0:
							ref = Color( 0.2, 0.2, 0.2, 1.0f );
						break;
						case 1:
							ref = Color::grey;
						break;
						case 2:
							ref = Color();
						break;
					}
					graphic = std::auto_ptr<Sprite>( new Sprite( "BMantle.tga", BEXTENT, BEXTENT, 48, 48, ref ) );
				break;
				case 1: graphic = std::auto_ptr<Sprite>( new Sprite( "BSoil.tga", BEXTENT, BEXTENT, 48, 48 ) );
				break;
				case 2: graphic = std::auto_ptr<Sprite>( new Sprite( "BGrass.tga", BEXTENT, BEXTENT, 48, 48 ) );
				break;
			}

			//Actor Body
			{
				b2BodyDef actorBodyDef;
				actorBodyDef.type = b2_staticBody;
				actorBodyDef.userData = this;
				actorBodyDef.position.Set( pos.x / PTM_RATIO, pos.y / PTM_RATIO );
				actorBodyDef.angle = 0;
				body = World::get()->CreateBody( &actorBodyDef );
			}
			// Actor Shape
			// Square made from an edge loop. Collision should be smooth.
			{
				b2FixtureDef fixtureDef;
				b2Vec2 vs[4];

				vs[0].Set( -graphic->getHwidth() / PTM_RATIO, -graphic->getHheight() / PTM_RATIO );
				vs[1].Set( graphic->getHwidth() / PTM_RATIO, -graphic->getHheight() / PTM_RATIO );
				vs[2].Set( graphic->getHwidth() / PTM_RATIO, graphic->getHheight() / PTM_RATIO );
				vs[3].Set( -graphic->getHwidth() / PTM_RATIO, graphic->getHheight() / PTM_RATIO );
				b2ChainShape shape;
				shape.CreateLoop(vs, 4);
				fixtureDef.shape = &shape;

				fixtureDef.density = 1.0f;
				fixtureDef.friction = 0.3f;
				body->CreateFixture( &fixtureDef );
			}
		}

		~block()
		{
			std::cout << "Destroying block... " << id << std::endl;
		};
		void update() {};
		void onCollission( Entity *collider ) {};
};

class Comet : public Actor
{
	public:
		explicit Comet() : Actor() {};
		explicit Comet( const glm::vec2& pos, float damping = 0.4f )
			: 	Actor( "Comet" )
		{
			graphic = std::auto_ptr<Sprite>( new Sprite( "Comet.tga", 32, 38, 32, 38 ) );
			{
				b2BodyDef actorBodyDef;
				actorBodyDef.type = b2_dynamicBody;
				actorBodyDef.userData = this;
				actorBodyDef.position.Set( pos.x / PTM_RATIO, pos.y / PTM_RATIO );
				actorBodyDef.angle = 0;
				actorBodyDef.fixedRotation = true;
				actorBodyDef.linearDamping = damping;
				body = World::get()->CreateBody( &actorBodyDef );
				b2FixtureDef fixtureDef;
				b2CircleShape actorBox;
				actorBox.m_radius = 16.0f / PTM_RATIO;
				fixtureDef.shape = &actorBox;
				fixtureDef.density = 1.0f;
				fixtureDef.friction = 0.3f;
				body->CreateFixture( &fixtureDef );
			}
		}

		~Comet()
		{
			std::cout << "Destroying Comet... " << id << std::endl;
		};

		void update() {};
		void onCollission( Entity *collider )
		{
			//std::cout << "Comet " << id << " hits ";
			if( collider->tag == "Comet" )
			{
				return;
			}
			World::addForRemoval( this->body );
			graphic->visible = false;
			//Start death Scene.
			//condemn when death Scene done at last frame of play..
			condemned = true;
			if( collider->tag == "Player" )
			{
				//std::cout << "Player" << std::endl;
				World::changeScene( new GameOver() );
			}
			else if( collider->tag == "Wall" )
			{
				//std::cout <<"Wall" << std::endl;
			}
			else if( collider->tag == "Ground" )
			{
				//std::cout << "Ground" << std::endl;
				Actor *p = static_cast<Actor*>( collider );
				World::addForRemoval( p->body  );
				p->graphic->visible = false;
				p->condemned = true;
			}
		};
};

class earth : public Scene
{
	public:
		explicit earth()
			:	lastComet(0.0),
				cometInterval(1.0),
				lastTick(0.0),
				worldTranslate(0.0f),
				groundLevel(0),
				cometRange(3),
				cometMin(2),
				fastestComet(4)
		{

		};
		~earth() { std::cout << "Destroying Earth..." << std::endl; };

		void init()
		{
			terran = new player( glm::vec2( Window::getWidth() >> 1, Window::getHeight() >> 1 )  );
			checkPoint = Window::getHeight() - 4*BEXTENT;
			add( terran );
			srand( time(0) );
			block *ground = 0;

			// Terrain Generation
			for( unsigned int i = BEXTENT/2.0f; i < Window::getWidth(); i+=BEXTENT )
			{
				ground = new block( glm::vec2( i, Window::getHeight() - BEXTENT/2.0f ), 0 );
				add( ground );
				ground = new block( glm::vec2( i, Window::getHeight() - ( BEXTENT + BEXTENT/2.0f ) ), 0 );
				add( ground );
				ground = new block( glm::vec2( i, Window::getHeight() - ( BEXTENT*2.0f + BEXTENT/2.0f ) ), 1 );
				add( ground );
				ground = new block( glm::vec2( i, Window::getHeight() - ( BEXTENT*3.0f + BEXTENT/2.0f ) ), 2 );
				add( ground );
			}

			leftWall = new wall( glm::vec2( 0, 0 ), glm::vec2( 0, Window::getHeight() ) );
			add( leftWall );
			rightWall = new wall( glm::vec2( Window::getWidth() >> 1, 0 ), glm::vec2( 240, Window::getHeight() ) );
			add( rightWall );
			floor = new wall( glm::vec2( 0, ( Window::getHeight() >> 1 ) + BEXTENT ), glm::vec2( Window::getWidth(), ( Window::getHeight() >> 1 ) + BEXTENT ) );
			add( floor );
		}

		void update()
		{
			Scene::update();

			////////////////////////////////////////////////////////////////////////
			// Update Ground When player drops lower.
			///////////////////////////////////////////////////////////////////////
			if( terran->getPos().y * PTM_RATIO >= checkPoint )
			{
				worldTranslate = BEXTENT;
				checkPoint += BEXTENT;
				block *ground = 0;
				leftWall->body->SetTransform(b2Vec2( 0.f, ( groundLevel*BEXTENT ) / PTM_RATIO ), 0.f );
				rightWall->body->SetTransform(b2Vec2( ( Window::getWidth() >> 1 ) / PTM_RATIO, ( groundLevel*BEXTENT ) / PTM_RATIO ), 0.f );
				floor->body->SetTransform(b2Vec2( 0.f, ( ( Window::getHeight() >> 1 ) + BEXTENT + groundLevel*BEXTENT ) / PTM_RATIO ), 0.f );
				for( unsigned int i = BEXTENT/2.0f; i < Window::getWidth(); i+=BEXTENT )
				{
					ground = new block( glm::vec2( i, Window::getHeight() + ( groundLevel*BEXTENT + BEXTENT/2.0f ) ), 0 );
					add( ground );
				}
				groundLevel++;
			}

			////////////////////////////////////////////////////////////////////////
			// Update Comets
			///////////////////////////////////////////////////////////////////////
			lastComet += Window::tick() - lastTick;
			lastTick = Window::tick();
			if( lastComet > cometInterval )
			{
				lastComet = 0.0;
				for( int i = 0; i < ( rand() % cometRange ) + cometMin; ++i )
				{
					add( new Comet( glm::vec2( ( rand() % 10 ) * BEXTENT + BEXTENT*0.5f, -CEXTENT - CEXTENT * ( rand() % 2 ) ),
									static_cast<float>( ( ( rand() % 2 ) + fastestComet ) ) / 10.0f ) );
				}
			}
		};

		void draw()
		{
			glTranslatef( 0.0f, -worldTranslate, 0.0f );
			Scene::draw();
			worldTranslate = 0.0f;
		};

	private:
		///////////////////////////////
		// Comet Logic members
		double lastComet;
		double lastTick;
		// Increase for next level..
		double cometInterval;
		// Increase for next level..
		int cometRange;
		int cometMin;
		// Speeds
		int fastestComet;

		////////////////////////////
		// Ground logic members.
		float checkPoint;
		float worldTranslate;
		int groundLevel;

		player *terran;
		wall *floor;
		wall *leftWall;
		wall *rightWall;
};

///////////////////////////////////////////////////////////////////////////////
// Title Screen
///////////////////////////////////////////////////////////////////////////////
class home : public Scene
{
	public:
		home()
		{
			Font *f =  Resources::grabFont( "ProggySquare.ttf", 36.0f );
			title = Label( "THE MOON ISA", f, glm::vec2( Window::getWidth() >> 1, 25.0f ),  Color::purple );
			buttons["New Game"] = Button( "New Game", f, glm::vec2( Window::getWidth() >> 1, 150 ) );
			buttons["Options"] = Button( "Options", f, glm::vec2( Window::getWidth() >> 1, 200 ) );
		}
		~home()  {}

		void init()
		{
			////////////////////////////////////////////////////////////////////////
			// Blocks
			///////////////////////////////////////////////////////////////////////
			for( int i = BEXTENT/2.0f; i < Window::getWidth();i+=BEXTENT )
				for( int j = BEXTENT/2.0f; j < Window::getHeight() + BEXTENT; j+=BEXTENT )
					add( new block( glm::vec2( i, j ), 0 ) );

		}

		void update()
		{
			Scene::update();

			if( Input::isKeyPressed( Input::ENTER ) )
				World::changeScene( new earth() );
			if( buttons["New Game"].update() )
				World::changeScene( new earth() );
		}

		void draw()
		{
			Scene::draw();
			title.draw();
			buttons["New Game"].draw();
			buttons["Options"].draw();
		}

	private:
		std::map< std::string, Button > buttons;
		Label title;
};

#endif
