#include "Scene.h"
#include "Entity.h"
#include <algorithm>
#include <iostream>
#include "Utils.h"

using namespace slge;

Scene::Scene()
	:	entityIdCounter(0),
		stage( b2World( b2Vec2( 0.0f, 9.8f ) ) ),
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
	entities.emplace_back( std::unique_ptr<Entity>( ent ) );
}

void Scene::baseUpdate()
{
	std::for_each( entities.begin(), entities.end(),
						[]( std::unique_ptr<Entity>& e ){ e->update(); } );
}

void Scene::baseDraw()
{
		std::for_each( entities.begin(), entities.end(),
							[]( std::unique_ptr<Entity>& e ){ e->draw(); } );
}