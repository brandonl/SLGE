#ifndef ENTITY_H
#define ENTITY_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <string>
#include <iostream>
#include <Box2D.h>

typedef b2Vec2 vec2;

namespace slge
{
	class scene;

	class entity
	{
		public:
			explicit entity() {};
			explicit entity( const std::string tag ) : tag(tag), condemned(false) {};
			virtual ~entity() = 0;

			virtual void update() = 0;
			virtual void draw() const = 0;
			virtual void on_collission( entity *collider ) = 0;
			virtual const vec2& get_pos() const = 0;
	
			unsigned int id;
			std::string tag;
			bool condemned;
	};
};
#endif
