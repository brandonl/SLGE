#ifndef ENTITY_H
#define ENTITY_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <string>
#include <iostream>
#include <Box2D.h>

namespace slge
{
	class Scene;

	class Entity
	{
		public:
			explicit Entity() {};
			explicit Entity( const std::string tag ) : tag(tag), condemned(false) {};
			virtual ~Entity() = 0;

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
