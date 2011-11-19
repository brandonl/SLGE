#include "block.h"
#include "input.h"

using namespace sgf;

block::block( const glm::vec2& pos ) 
	:	entity( "Block", pos, SQWIDTH, SQWIDTH ), 
		center(pos),
		collided(false)
{
}

void block::update()
{
	/*
	if( input::is_key_pressed( input::DOWN ) )
		//move( input::DOWN );
	else if( input::is_key_pressed( input::LEFT ) )
		//move( input::LEFT );
	else if( input::is_key_pressed( input::RIGHT ) )
		//move( input::RIGHT );
	else if( input::is_key_pressed( ' ' ) )
		//rotate();
	*/
}

void block::draw()
{
}

bool block::did_collide() const
{
	return collided;
}