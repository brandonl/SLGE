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
		typedef std::vector< std::unique_ptr<Entity>> EntityList;

		public:
			Scene();
			virtual ~Scene();

			void add( Entity* ent );
			void loadGameEntities();
			void update();
			void draw();
			void changeLayer( unsigned l );
			void BeginContact( b2Contact* contact );
			void EndContact( b2Contact* contact );

			b2Body* createBody( const b2BodyDef &bodyDef ) const;

		private:
			virtual void doUpdate() = 0;
			virtual void preDraw() = 0;
			virtual void postDraw() = 0;
			virtual void doLoadGameEntities() = 0;

		private:
			void			baseLoadGameEntities();
			void			baseUpdate();
			void			baseDraw();

			unsigned		entityIdCounter;
			// Still logically const
			mutable		b2World		stage;
			unsigned		drawLayer;
			DebugDraw	debugDraw;
			EntityList	entities;

		public:
			enum
			{
				debug		=	0x0000,
				noDebug	=	0x0001
			};
	};

	inline void Scene::loadGameEntities()
	{
		baseLoadGameEntities();
		doLoadGameEntities();
	}

	inline void Scene::update()
	{
		baseUpdate();
		doUpdate();
	}

	inline void Scene::draw()
	{
		preDraw();
//#ifdef NDEBUG
		if( drawLayer == debug )
//#endif
			stage.DrawDebugData();
		baseDraw();
		postDraw();
	}

	inline b2Body* Scene::createBody( const b2BodyDef &bodyDef ) const
	{
		return stage.CreateBody( &bodyDef );
	}

	inline void Scene::changeLayer( unsigned l )
	{
		drawLayer = l;
	}
};

#endif
