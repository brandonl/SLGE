#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
#include <Box2D.h>

namespace slge
{
	class Scene;

	class Entity
	{
		public:
			explicit Entity( const std::string tag = "" ) : tag(tag), condemned(false) 
			{
				std::cout << "Create entity: " << tag << std::endl;
			};
			virtual ~Entity() { std::cout << "Destroying entity\n"; };

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
