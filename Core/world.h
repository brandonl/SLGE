#ifndef WORLD_H
#define WORLD_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <windows.h>
#include <gl/gl.h>
#include "scene.h"
#include "render.h"
#include <list>


namespace slge
{
	static const float DELTA_TIME = 1.0f/60.0f;
	class world : public b2ContactListener
	{
		public:
			world();
			~world();
			void init( /*settings*/ );

			static void update();
			static void draw();
			static b2World* get();
			static void add_for_removal( b2Body *ent );
			static void change_scene( scene *scn );
			static void change_layer( unsigned int l );
			static void clean();

			static void pause();
			// More powerful than pause cannot be undone with 'p'
			static void stop();
			static float delta_time;

		    // Callbacks for contact listnener derived classes.
			void BeginContact( b2Contact* contact );
			void EndContact( b2Contact* contact );

		private:
			static void do_change();

			std::shared_ptr<scene> current;
			std::shared_ptr<scene> last;
			b2World *phys_world;
			std::list<b2Body*> scheduled_for_removal;
			debug_draw debug_draw;

			// Controlled by game and scenes.
			unsigned int layer;
			bool paused;
			bool stopped;

			// Singleton
			static world *instance;
	};

	enum Special
	{
		FOOT = 2
	};
};

#endif
