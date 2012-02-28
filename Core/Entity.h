#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <cstdio>
#include <Box2D.h>

namespace slge
{
	class Scene;

	class Entity // : public Node
	{
		public:
			explicit Entity( const std::string tag = "" ) : tag(tag), condemned(false) 
			{
				printf( "Create entity: %s\n", tag.c_str() );
			}

			virtual ~Entity() 
			{ 
				printf( "Destroying entity: %s\n", tag.c_str() );
			}

			virtual void update() = 0;
			virtual void draw() const = 0;
			virtual void onCollission( Entity *collider ) = 0;
			virtual const b2Vec2& getPos() const = 0;

			unsigned int id;
			std::string tag;
			bool condemned;
	};
};
#endif
