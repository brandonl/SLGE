#ifndef ACTOR_H
#define ACTOR_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "Entity.h"
#include "Sprite.h"
#include <Box2D.h>

namespace slge
{
	class Actor : public Entity
	{
		public:
			explicit Actor() : Entity(), body(0), graphic(0) {};
			explicit Actor( const std::string& tag );
			virtual ~Actor() = 0;

			virtual void draw() const;
			virtual void update();
			const b2Vec2& getPos() const;
			virtual void handleSpecial();

			b2Body *body;
			std::auto_ptr<Sprite> graphic;
	};
};

#endif
