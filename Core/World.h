#ifndef WORLD_H
#define WORLD_H

#include <windows.h>
#include <gl/gl.h>
#include "Scene.h"
#include "Render.h"
#include <list>


namespace slge
{
	static const float DELTA_TIME = 1.0f/60.0f;
	class World : public b2ContactListener
	{
		public:
			World();
			~World();
			void init( /*settings*/ );

			static void update();
			static void draw();
			static b2World* get();
			static void addForRemoval( b2Body *ent );
			static void changeScene( Scene *scn );
			static void changeLayer( unsigned int l );
			static void clean();

			static void pause();
			// More powerful than pause cannot be undone with 'p'
			static void stop();
			static float deltaTime;

		    // Callbacks for contact listnener derived classes.
			void BeginContact( b2Contact* contact );
			void EndContact( b2Contact* contact );

		private:
			static void doChange();

			std::shared_ptr<Scene> current;
			std::shared_ptr<Scene> last;
			b2World *physWorld;
			std::list<b2Body*> scheduledForRemoval;
			DebugDraw DebugDraw;

			// Controlled by game and scenes.
			unsigned int layer;
			bool paused;
			bool stopped;

			// Singleton
			static World *instance;
	};

	enum Special
	{
		FOOT = 2
	};
};

#endif
