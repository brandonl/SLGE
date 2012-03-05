#include "Entity.h"
#include "Scene.h"

using namespace slge;

Entity::Entity( const std::string &groupName, Scene *parent )
	:  group(groupName), 
		condemned(false),
		parent(parent)
{	}
void Entity::load()
{
	doLoad();
}

void Entity::update()
{
	doUpdate();
}

void Entity::draw() const
{
	doDraw();
}

void Entity::setParent( const Scene *p )
{
	parent = p;
}

const Scene* Entity::getParent() const
{
	return parent;
}