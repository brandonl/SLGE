#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <Box2D.h>
#include "Utils.h"
#include "Render.h"

namespace slge
{
	class Entity;

	class Scene : public b2ContactListener, private Uncopyable
	{
		public:
			Scene();
			virtual ~Scene();

			void add( Entity* ent );
			void update();
			void draw();
			void changeLayer( unsigned l );

			b2Body* createBody( const b2BodyDef &bodyDef );

		protected:
			virtual void doUpdate();
			virtual void doDraw();

		private:
			unsigned		entityIdCounter;
			b2World		stage;
			unsigned		drawLayer;
			DebugDraw	debugDraw;
			std::vector< std::unique_ptr<Entity> > entities;

		public:
			enum
			{
				debug		=	0x0000,
				noDebug	=	0x0001
			};
	};

	inline void Scene::update()
	{
		doUpdate();
	}

	inline void Scene::draw()
	{
		if( drawLayer == noDebug )
			doDraw();
		else
			stage.DrawDebugData();
	}

	inline b2Body* Scene::createBody( const b2BodyDef &bodyDef )
	{
		return stage.CreateBody( &bodyDef );
	}

	inline void Scene::changeLayer( unsigned l )
	{
		drawLayer = l;
	}
};

#endif
