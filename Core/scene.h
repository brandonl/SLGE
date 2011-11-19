#ifndef SCENE_H
#define SCENE_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <list>
#include <iostream>

namespace slge
{
	class entity;

	class scene
	{
		public:
			explicit scene();
			virtual ~scene();

			// You CANNOT creat actors inside constructor of scenes...
			// They MUST be created within the init().
			virtual void init() = 0;
			virtual void update();
			virtual void draw();

			void			add( entity* ent );
			//void			remove( entity* ent );
			//const entity*	find( entity *ent );
			//void			swap( entity *ent );
			//void			clear();

			std::list< std::shared_ptr<entity> > entities;

		private:
			unsigned int entity_id_counter;
	};

};

#endif
