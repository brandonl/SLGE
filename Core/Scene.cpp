#include "Scene.h"
#include "Entity.h"
#include <algorithm>
#include <iostream>
#include "Utils.h"
#include "Settings.h"

using namespace slge;

Scene::Scene()
	:	entityIdCounter(0),
		stage( b2World( b2Vec2( 0.0f, SLGE_GRAVITY ) ) ),
		drawLayer(noDebug)
{
	debugDraw.SetFlags( b2Draw::e_shapeBit );
	stage.SetDebugDraw( &debugDraw );
	stage.SetContactListener(this);
	printf( "Creating Scene...\n" );
}

Scene::~Scene()
{
	printf( "Destroying Scene...\n" );
}

void Scene::add( Entity *ent )
{
	ent->id = entityIdCounter++;
	ent->setParent( this );
	entities.emplace_back( std::unique_ptr<Entity>( ent ) );
}

void Scene::baseLoadGameEntities()
{
	std::for_each( entities.begin(), entities.end(),
						[]( std::unique_ptr<Entity>& e ){ e->load(); } );
}

void Scene::baseUpdate()
{
	std::for_each( entities.begin(), entities.end(),
						[]( std::unique_ptr<Entity>& e ){ e->update(); } );
	stage.Step( DELTA_TIMEF, 8, 3 );
	stage.ClearForces();
}

void Scene::baseDraw()
{
		std::for_each( entities.begin(), entities.end(),
							[]( std::unique_ptr<Entity>& e ){ e->draw(); } );
}

void Scene::BeginContact( b2Contact* contact )
{
	printf( "Contact\n" );
}

void Scene::EndContact( b2Contact* contact )
{
	printf( "End contact\n" );
}