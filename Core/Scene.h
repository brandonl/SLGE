#ifndef SCENE_H
#define SCENE_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <list>
#include <iostream>

namespace slge
{
	class Entity;

	class Scene
	{
		public:
			explicit Scene();
			virtual ~Scene();

			// You CANNOT creat actors inside constructor of scenes...
			// They MUST be created within the init().
			virtual void init() = 0;
			virtual void update();
			virtual void draw();

			void			add( Entity* ent );
			//void			remove( Entity* ent );
			//const Entity*	find( Entity *ent );
			//void			swap( Entity *ent );
			//void			clear();

			std::list< std::shared_ptr<Entity> > entities;

		private:
			unsigned int entityIdCounter;
	};

};

#endif
