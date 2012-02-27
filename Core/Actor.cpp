#include "Actor.h"
#include "World.h"
#include <iostream>
#include "Defines.h"

using namespace slge;

Actor::Actor( const std::string& tag )
	:	Entity(tag),
		body(0)
{
}

Actor::~Actor()
{
}

void Actor::draw() const
{
	if( graphic.get() )
	{
		glPushMatrix();
		glTranslatef( getPos().x * PTM_RATIO, getPos().y * PTM_RATIO, 0.0f );
		graphic->draw();
		glPopMatrix();
	}
}

void Actor::update()
{
	graphic->update();
}

const b2Vec2& Actor::getPos() const
{
	return body->GetPosition();
}

void Actor::handleSpecial()
{
}
