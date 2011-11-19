#include "actor.h"
#include "world.h"
#include <iostream>

using namespace slge;

actor::actor( const std::string& tag )
	:	entity(tag),
		body(0)
{
}

actor::~actor()
{
}

void actor::draw() const
{
	if( graphic.get() )
	{
		glPushMatrix();
		glTranslatef( get_pos().x * PTM_RATIO, get_pos().y * PTM_RATIO, 0.0f );
		graphic->draw();
		glPopMatrix();
	}
}

void actor::update()
{
	graphic->update();
}

const vec2& actor::get_pos() const
{
	return body->GetPosition();
}

void actor::handle_special()
{
}