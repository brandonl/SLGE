#include "world.h"
#include "window.h"
#include <iostream>
#include "entity.h"
#include "input.h"
#include "actor.h"

using namespace slge;

world *world::instance = NULL;

world::world()
{
	if( instance != NULL )
		std::cerr << "Only one world context may be active at a time.";
	instance = this;
}

world::~world()
{
	delete phys_world;
}

void world::init()
{
	layer = 0;
	paused = false;
	stopped = false;
	phys_world = new b2World( b2Vec2( 0.0f, 9.8f ), true );
	debug_draw.SetFlags( b2Draw::e_shapeBit );
	phys_world->SetDebugDraw( &debug_draw );
	phys_world->SetContactListener(this);
}

b2World* world::get()
{
	return instance->phys_world;
}

void world::add_for_removal( b2Body *ent )
{
	entity *condemned = static_cast<entity*>(ent->GetUserData());
	for( auto it = instance->scheduled_for_removal.begin(); it != instance->scheduled_for_removal.end(); ++it )
	{
		entity *on_death_row = (entity*)(*it)->GetUserData();
		if( on_death_row->id == condemned->id )
			return;
	}
	instance->scheduled_for_removal.push_back( ent );
}

void world::update()
{
	if( input::is_key_pressed( 'P' ) )
		instance->pause();

	if( !instance->paused && !instance->stopped )
	{
		instance->phys_world->Step( DELTA_TIME, 8, 3 );
		instance->clean();
		if( instance->last != instance->current )
		{
			std::cout << "Changed scene.."<<std::endl;
			instance->do_change();
		}
		instance->current->update();
	}
}

void world::draw()
{
	if( instance->layer == 1 )
		instance->phys_world->DrawDebugData();
	else
		instance->current->draw();
}

void world::change_scene( scene *scn )
{
	// First scene set.
	if( !instance->current )
	{
		std::cout << "Start scene.." << std::endl;
		instance->current = instance->last = std::shared_ptr<scene>( scn );
		instance->current->init();
		return;
	}
	instance->last = instance->current;
	instance->current = std::shared_ptr<scene>( scn );
}

void world::do_change()
{
	instance->last = instance->current;
	std::cout << "Cleaning and creating new world... " << std::endl;
	delete instance->phys_world;
	instance->phys_world = new b2World( b2Vec2( 0.0f, 12.0f ), true );
	instance->phys_world->SetDebugDraw( &instance->debug_draw );
	instance->phys_world->SetContactListener(instance);
	instance->current->init();
}

void world::clean()
{
	for( auto it = instance->scheduled_for_removal.begin(); it != instance->scheduled_for_removal.end(); ++it )
	{
		entity *on_death_row = static_cast<entity*>( (*it)->GetUserData() );
		std::cout << "Deleteing " << on_death_row->tag << " " << on_death_row->id << std::endl;
		instance->phys_world->DestroyBody( *it );
	}
	instance->scheduled_for_removal.clear();
}

void world::change_layer( unsigned int l )
{
	instance->layer = l;
}

void world::pause()
{
	instance->paused = instance->paused ? false : true;
}

void world::stop()
{
	instance->stopped = instance->stopped ? false : true;
}

void world::BeginContact( b2Contact* contact )
{
	entity *a = static_cast<entity*>( contact->GetFixtureA()->GetBody()->GetUserData() );
	entity *b = static_cast<entity*>( contact->GetFixtureB()->GetBody()->GetUserData() );
	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	if( (unsigned int)fixtureUserDataA == FOOT )
	{
		actor *act = dynamic_cast<actor*>( a );
		act->handle_special();
	}

	if( (unsigned int)fixtureUserDataB == FOOT )
	{
		actor *act = dynamic_cast<actor*>( b );
		act->handle_special();
	}

	//std::cout << "A " << a->tag << " " << a->id << " invoked on " << " B " << b->tag << " " << b->id << std::endl;
	a->on_collission( b );
	//std::cout << "B " << b->tag << " " << b->id << " invoked on " << " A " << a->tag << " " << a->id << std::endl;
	b->on_collission( a );
}

void world::EndContact( b2Contact* contact )
{
}

