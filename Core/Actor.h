#ifndef ACTOR_H
#define ACTOR_H

#include "Entity.h"
#include "Sprite.h"
#include <Box2D.h>
#include "Utils.h"

namespace slge
{
	class Actor : public Entity, private Uncopyable
	{
		//public:
		//	explicit Actor( const std::string& tag = "" );
		//	virtual ~Actor() = 0;

		//	virtual void update();
		//	virtual void draw() const;
		//	const b2Vec2& getPos() const;
		//	virtual void handleSpecial();

		//	b2Body *body;
		//	std::auto_ptr<Sprite> graphic;
	};
};

#endif
