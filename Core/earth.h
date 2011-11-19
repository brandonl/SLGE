#ifndef TEST_H
#define TEST_H

#include "scene.h"
#include "actor.h"
#include "world.h"
#include "window.h"
#include <Box2D.h>
#include <ctime>
#include "resourcemodule.h"
#include "button.h"
#include "label.h"

using namespace slge;

static const float BEXTENT = 48.0f;
static const float PEXTENT = 32.0f;
static const float CEXTENT = 48.0f;

class game_over : public scene
{
	public:
		explicit game_over() 
		{
			banner = label( "GAME OVER", resources::grab_font( "ProggySquare.ttf", 62.0f ), vec2( window::get_width() >> 1, window::get_height() >> 1 ), color() );
		}
		~game_over() {	std::cout << "Destroying game over... " << std::endl;}

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
		label banner;
};

//////////////////////////////////////////////////////////////////////////////
// Gameplay
//////////////////////////////////////////////////////////////////////////////
class player : public actor
{
	public:
		explicit player() : actor() {};
		explicit player( const vec2& pos )
			:	actor( "Player" ),
				in_air(true)
		{
			//graphic = std::auto_ptr<sprite>( new sprite( "Res/Ogmo.tga", 8, 8, 64, 32 ) );
			graphic = std::auto_ptr<sprite>( new sprite( "Ogmo2.tga", 32, 32, 256, 128 ) );
			graphic->add( "Stand", 0, 0, 0, 0.0f );
			graphic->add( "Run", 0, 3, 0, 12.0f );
			graphic->add( "Jump", 0, 0, 1, 0.0f );
			graphic->play( "Run" );

			//Actor Body
			{
				b2BodyDef actor_body_def;
				actor_body_def.type = b2_dynamicBody;
				actor_body_def.userData = this;
				actor_body_def.position.Set( pos.x / PTM_RATIO, pos.y / PTM_RATIO );
				actor_body_def.angle = 0;
				body = world::get()->CreateBody( &actor_body_def );
			}
			// Actor Shape
			{
				b2FixtureDef fixture_def;

				b2PolygonShape actor_box;
				actor_box.SetAsBox( ( graphic->get_hwidth() - 6 ) / PTM_RATIO, graphic->get_hheight() / PTM_RATIO );
				fixture_def.shape = &actor_box;
				fixture_def.density = 1.0f;
				fixture_def.friction = 0.0f;
				body->CreateFixture( &fixture_def );
				body->SetFixedRotation(true);
				body->SetGravityScale( 8.0f );
				actor_box.SetAsBox( ( graphic->get_hwidth() - 8.1f ) / PTM_RATIO, 0.3f / PTM_RATIO, vec2( 0, ( graphic->get_hheight() - 0.3f) / PTM_RATIO ), 0 );
				// Create foot...
				fixture_def.friction = 1.0f;
				b2Fixture* footSensorFixture = body->CreateFixture(&fixture_def);
				//Special case looked for in world...
				footSensorFixture->SetUserData( (void*)FOOT );
			}
		}

		~player() { std::cout << "Destroying player... " << id << std::endl;};

		void update() 
		{
			actor::update();
			if( input::is_key_held( input::LEFT ) )
			{
				body->SetAwake( true );
				float y = body->GetLinearVelocity().y;
				body->SetLinearVelocity( vec2( -6.0f, y ) );
			}
			
			if( input::is_key_held( input::RIGHT ) )
			{
				body->SetAwake( true );
				float y = body->GetLinearVelocity().y;
				body->SetLinearVelocity( vec2( 6.0f, y ) );
			}

			if( input::is_key_pressed( input::UP ) && !in_air )
			{
				in_air = true;
				body->SetAwake( true );
				float x = body->GetLinearVelocity().x;
				body->SetLinearVelocity( vec2( x, -26.0f ) );
			}
		};

		void handle_special()
		{
			in_air = false;
		}

		void on_collission( entity *collider ) 
		{
		};

		bool in_air;
};

class wall : public actor
{
	public:
		explicit wall() : actor() {};
		explicit wall( const vec2& pos, const vec2& pos2 )
			: actor( "Wall" )
		{
			b2EdgeShape edge_shape;
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &edge_shape;
			myFixtureDef.density = 1;
			b2BodyDef bd;
			bd.userData = this;
			bd.type = b2_staticBody;
			bd.angle = 0;
			bd.position.Set( pos.x / PTM_RATIO, pos.y / PTM_RATIO );
			edge_shape.Set( b2Vec2( pos.x / PTM_RATIO, pos.y / PTM_RATIO ), b2Vec2( pos2.x / PTM_RATIO, pos2.y / PTM_RATIO ) );
			body = world::get()->CreateBody(&bd);
			body->CreateFixture(&myFixtureDef);
		}

		~wall() { std::cout << "Destroying wall... " << id << std::endl;};
		void draw() {};
		void update() 
		{
		};
		void on_collission( entity *collider ) {};
};

class block : public actor
{
	public:

		explicit block() : actor() {};
		explicit block( const vec2& pos, int level )
			: actor( "Ground" )
		{
			int randy = rand() % 3;
			color ref;
			switch( level )
			{
				case 0: 
					switch( randy )
					{
						case 0:
							ref = color( 0.2, 0.2, 0.2, 1.0f );
						break;
						case 1:
							ref = color::grey;
						break;
						case 2:
							ref = color();
						break;
					}
					graphic = std::auto_ptr<sprite>( new sprite( "BMantle.tga", BEXTENT, BEXTENT, 48, 48, ref ) );
				break;
				case 1: graphic = std::auto_ptr<sprite>( new sprite( "BSoil.tga", BEXTENT, BEXTENT, 48, 48 ) );
				break;
				case 2: graphic = std::auto_ptr<sprite>( new sprite( "BGrass.tga", BEXTENT, BEXTENT, 48, 48 ) );
				break;
			}

			//Actor Body
			{
				b2BodyDef actor_body_def;
				actor_body_def.type = b2_staticBody;
				actor_body_def.userData = this;
				actor_body_def.position.Set( pos.x / PTM_RATIO, pos.y / PTM_RATIO );
				actor_body_def.angle = 0;
				body = world::get()->CreateBody( &actor_body_def );
			}
			// Actor Shape
			// Square made from an edge loop. Collision should be smooth.
			{
				b2FixtureDef fixture_def;
                b2Vec2 vs[4];

                vs[0].Set( -graphic->get_hwidth() / PTM_RATIO, -graphic->get_hheight() / PTM_RATIO );
                vs[1].Set( graphic->get_hwidth() / PTM_RATIO, -graphic->get_hheight() / PTM_RATIO );
				vs[2].Set( graphic->get_hwidth() / PTM_RATIO, graphic->get_hheight() / PTM_RATIO );
				vs[3].Set( -graphic->get_hwidth() / PTM_RATIO, graphic->get_hheight() / PTM_RATIO );
                b2ChainShape shape;
                shape.CreateLoop(vs, 4);
				fixture_def.shape = &shape;

				fixture_def.density = 1.0f;
				fixture_def.friction = 0.3f;
				body->CreateFixture( &fixture_def );
			}
		}

		~block() 
		{	
			std::cout << "Destroying block... " << id << std::endl;
		};
		void update() {};
		void on_collission( entity *collider ) {};
};

class comet : public actor
{
	public:
		explicit comet() : actor() {};
		explicit comet( const vec2& pos, float damping = 0.4f )
			: 	actor( "Comet" )
		{
			graphic = std::auto_ptr<sprite>( new sprite( "Comet.tga", 32, 38, 32, 38 ) );
			{
				b2BodyDef actor_body_def;
				actor_body_def.type = b2_dynamicBody;
				actor_body_def.userData = this;
				actor_body_def.position.Set( pos.x / PTM_RATIO, pos.y / PTM_RATIO );
				actor_body_def.angle = 0;
				actor_body_def.fixedRotation = true;
				actor_body_def.linearDamping = damping;
				body = world::get()->CreateBody( &actor_body_def );
				b2FixtureDef fixture_def;
				b2CircleShape actor_box;
				actor_box.m_radius = 16.0f / PTM_RATIO;
				fixture_def.shape = &actor_box;
				fixture_def.density = 1.0f;
				fixture_def.friction = 0.3f;
				body->CreateFixture( &fixture_def );
			}
		}

		~comet() 
		{
			std::cout << "Destroying comet... " << id << std::endl;
		};

		void update() {};
		void on_collission( entity *collider ) 
		{
			//std::cout << "Comet " << id << " hits ";
			if( collider->tag == "Comet" )
			{
				return;
			}
			world::add_for_removal( this->body );
			graphic->visible = false;
			//Start death scene.
			//condemn when death scene done at last frame of play..
			condemned = true;
			if( collider->tag == "Player" )
			{
				//std::cout << "Player" << std::endl;
				//world::change_scene( new game_over() );
			}
			else if( collider->tag == "Wall" )
			{
				//std::cout <<"Wall" << std::endl;
			}
			else if( collider->tag == "Ground" )
			{
				//std::cout << "Ground" << std::endl;
				actor *p = static_cast<actor*>( collider );
				world::add_for_removal( p->body  );
				p->graphic->visible = false;
				p->condemned = true;
			}
		};
};

class earth : public scene
{
	public:
		explicit earth() 
			:	last_comet(0.0),
				comet_interval(1.0),
				last_tick(0.0),
				world_translate(0.0f),
				ground_level(0),
				comet_range(3),
				comet_min(2),
				fastest_comet(4)
		{

		};
		~earth() { std::cout << "Destroying Earth..." << std::endl; };

		void init()
		{
			terran = new player( vec2( window::get_width() >> 1, window::get_height() >> 1 )  );
			check_point = window::get_height() - 4*BEXTENT;
			add( terran );
			srand( time(0) );
			block *ground = 0;

			// Terrain Generation
			for( unsigned int i = BEXTENT/2.0f; i < window::get_width(); i+=BEXTENT )
			{
				ground = new block( vec2( i, window::get_height() - BEXTENT/2.0f ), 0 );
				add( ground );
				ground = new block( vec2( i, window::get_height() - ( BEXTENT + BEXTENT/2.0f ) ), 0 );
				add( ground );
				ground = new block( vec2( i, window::get_height() - ( BEXTENT*2.0f + BEXTENT/2.0f ) ), 1 );
				add( ground );
				ground = new block( vec2( i, window::get_height() - ( BEXTENT*3.0f + BEXTENT/2.0f ) ), 2 );
				add( ground );
			}

			left_wall = new wall( vec2( 0, 0 ), vec2( 0, window::get_height() ) );
			add( left_wall );
			right_wall = new wall( vec2( window::get_width() >> 1, 0 ), vec2( 240, window::get_height() ) );
			add( right_wall ); 
			floor = new wall( vec2( 0, ( window::get_height() >> 1 ) + BEXTENT ), vec2( window::get_width(), ( window::get_height() >> 1 ) + BEXTENT ) );
			add( floor );
		}

		void update() 
		{ 
			scene::update(); 

			////////////////////////////////////////////////////////////////////////
			// Update Ground When player drops lower.
			///////////////////////////////////////////////////////////////////////
			if( terran->get_pos().y * PTM_RATIO >= check_point )
			{
				world_translate = BEXTENT;
				check_point += BEXTENT;
				block *ground = 0;
				left_wall->body->SetTransform( vec2( 0.f, ( ground_level*BEXTENT ) / PTM_RATIO ), 0.f );
				right_wall->body->SetTransform( vec2( ( window::get_width() >> 1 ) / PTM_RATIO, ( ground_level*BEXTENT ) / PTM_RATIO ), 0.f );
				floor->body->SetTransform( vec2( 0.f, ( ( window::get_height() >> 1 ) + BEXTENT + ground_level*BEXTENT ) / PTM_RATIO ), 0.f );
				for( unsigned int i = BEXTENT/2.0f; i < window::get_width(); i+=BEXTENT )
				{
					ground = new block( vec2( i, window::get_height() + ( ground_level*BEXTENT + BEXTENT/2.0f ) ), 0 );
					add( ground );
				}
				ground_level++;
			}

			////////////////////////////////////////////////////////////////////////
			// Update Comets
			///////////////////////////////////////////////////////////////////////
			last_comet += window::tick() - last_tick;
			last_tick = window::tick();
			if( last_comet > comet_interval )
			{
				last_comet = 0.0;
				for( int i = 0; i < ( rand() % comet_range ) + comet_min; ++i )
				{
					add( new comet( vec2( ( rand() % 10 ) * BEXTENT + BEXTENT*0.5f, -CEXTENT - CEXTENT * ( rand() % 2 ) ), 
									static_cast<float>( ( ( rand() % 2 ) + fastest_comet ) ) / 10.0f ) );
				}
			}
		};

		void draw() 
		{ 
			glTranslatef( 0.0f, -world_translate, 0.0f );
			scene::draw(); 
			world_translate = 0.0f;
		};

	private:
		///////////////////////////////
		// Comet Logic members
		double last_comet;
		double last_tick;
		// Increase for next level..
		double comet_interval;
		// Increase for next level..
		int comet_range;
		int comet_min;
		// Speeds
		int fastest_comet;

		////////////////////////////
		// Ground logic members.
		float check_point;
		float world_translate;
		int ground_level;

		player *terran;
		wall *floor;
		wall *left_wall;
		wall *right_wall;
};

///////////////////////////////////////////////////////////////////////////////
// Title Screen
///////////////////////////////////////////////////////////////////////////////
class home : public scene
{
	public:
		explicit home() 
		{
			font *f =  resources::grab_font( "ProggySquare.ttf", 36.0f );
			title = label( "THE MOON ISA", f, vec2( window::get_width() >> 1, 25.0f ),  color::purple );
			buttons["New Game"] = button( "New Game", f, vec2( window::get_width() >> 1, 150 ) );
			buttons["Options"] = button( "Options", f, vec2( window::get_width() >> 1, 200 ) );
		}
		~home()  {}

		void init()
		{
			////////////////////////////////////////////////////////////////////////
			// Blocks
			///////////////////////////////////////////////////////////////////////
			for( int i = BEXTENT/2.0f; i < window::get_width();i+=BEXTENT )
				for( int j = BEXTENT/2.0f; j < window::get_height() + BEXTENT; j+=BEXTENT )
					add( new block( vec2( i, j ), 0 ) );

		}

		void update()
		{
			scene::update();

			if( input::is_key_pressed( input::ENTER ) )
				world::change_scene( new earth() );
			if( buttons["New Game"].update() )
				world::change_scene( new earth() );
		}

		void draw()
		{			
			scene::draw();
			title.draw();
			buttons["New Game"].draw();
			buttons["Options"].draw();
		}

	private:
		std::map< std::string, button > buttons;
		label title;
};

#endif