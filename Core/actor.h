#ifndef ACTOR_H
#define ACTOR_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "entity.h"
#include "sprite.h"

namespace slge
{
	class actor : public entity
	{
		public:
			explicit actor() : entity(), body(0), graphic(0) {};
			explicit actor( const std::string& tag );
			virtual ~actor() = 0;

			virtual void draw() const;
			virtual void update();
			const vec2& get_pos() const;
			virtual void handle_special();

			b2Body *body;
			std::auto_ptr<sprite> graphic;
	};
};

#endif