#include "World.h"
#include "Window.h"
#include <iostream>
#include "Entity.h"
#include "Input.h"
#include "Actor.h"

using namespace slge;

World *World::instance = NULL;

World::World()
{
	if( instance != NULL )
		std::cerr << "Only one World context may be active at a time.";
	instance = this;
}

World::~World()
{
	delete physWorld;
}

void World::init()
{
	layer = 0;
	paused = false;
	stopped = false;
	physWorld = new b2World( b2Vec2( 0.0f, 9.8f ) );
	DebugDraw.SetFlags( b2Draw::e_shapeBit );
	physWorld->SetDebugDraw( &DebugDraw );
	physWorld->SetContactListener(this);
}

b2World* World::get()
{
	return instance->physWorld;
}

void World::addForRemoval( b2Body *ent )
{
	Entity *condemned = static_cast<Entity*>(ent->GetUserData());
	for( auto it = instance->scheduledForRemoval.begin(); it != instance->scheduledForRemoval.end(); ++it )
	{
		Entity *onDeathRow = (Entity*)(*it)->GetUserData();
		if( onDeathRow->id == condemned->id )
			return;
	}
	instance->scheduledForRemoval.push_back( ent );
}

void World::update()
{
	if( Input::isKeyPressed( 'P' ) )
		instance->pause();

	if( !instance->paused && !instance->stopped )
	{
		instance->physWorld->Step( DELTA_TIME, 8, 3 );
		instance->clean();
		if( instance->last != instance->current )
		{
			std::cout << "Changed Scene.."<<std::endl;
			instance->doChange();
		}
		instance->current->update();
	}
}

void World::draw()
{
	if( instance->layer == 1 )
		instance->physWorld->DrawDebugData();
	else
		instance->current->draw();
}

void World::changeScene( Scene *scn )
{
	// First Scene set.
	if( !instance->current )
	{
		std::cout << "Start Scene.." << std::endl;
		instance->current = instance->last = std::shared_ptr<Scene>( scn );
		instance->current->init();
		return;
	}
	instance->last = instance->current;
	instance->current = std::shared_ptr<Scene>( scn );
}

void World::doChange()
{
	instance->last = instance->current;
	std::cout << "Cleaning and creating new World... " << std::endl;
	delete instance->physWorld;
	instance->physWorld = new b2World( b2Vec2( 0.0f, 12.0f ) );
	instance->physWorld->SetDebugDraw( &instance->DebugDraw );
	instance->physWorld->SetContactListener(instance);
	instance->current->init();
}

void World::clean()
{
	for( auto it = instance->scheduledForRemoval.begin(); it != instance->scheduledForRemoval.end(); ++it )
	{
		Entity *onDeathRow = static_cast<Entity*>( (*it)->GetUserData() );
		std::cout << "Deleteing " << onDeathRow->tag << " " << onDeathRow->id << std::endl;
		instance->physWorld->DestroyBody( *it );
	}
	instance->scheduledForRemoval.clear();
}

void World::changeLayer( unsigned int l )
{
	instance->layer = l;
}

void World::pause()
{
	instance->paused = instance->paused ? false : true;
}

void World::stop()
{
	instance->stopped = instance->stopped ? false : true;
}

void World::BeginContact( b2Contact* contact )
{
	Entity *a = static_cast<Entity*>( contact->GetFixtureA()->GetBody()->GetUserData() );
	Entity *b = static_cast<Entity*>( contact->GetFixtureB()->GetBody()->GetUserData() );
	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	if( (unsigned int)fixtureUserDataA == FOOT )
	{
		Actor *act = dynamic_cast<Actor*>( a );
		act->handleSpecial();
	}

	if( (unsigned int)fixtureUserDataB == FOOT )
	{
		Actor *act = dynamic_cast<Actor*>( b );
		act->handleSpecial();
	}

	//std::cout << "A " << a->tag << " " << a->id << " invoked on " << " B " << b->tag << " " << b->id << std::endl;
	a->onCollission( b );
	//std::cout << "B " << b->tag << " " << b->id << " invoked on " << " A " << a->tag << " " << a->id << std::endl;
	b->onCollission( a );
}

void World::EndContact( b2Contact* contact )
{
}

