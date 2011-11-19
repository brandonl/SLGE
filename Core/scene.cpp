#include "scene.h"
#include "entity.h"

using namespace slge;

scene::scene()
	:	entity_id_counter(0)
{
	std::cout << "Creating scene..." << this << std::endl;
}

scene::~scene()
{
	std::cout << "Destroying scene..." << this << std::endl;
}

void scene::update()
{
	for( auto cit = entities.begin(); cit != entities.end(); ++cit )
	{
		if( (*cit)->condemned == true )
			cit = entities.erase( cit );
	}
	
	for( auto cit = entities.begin(); cit != entities.end(); ++cit )
		(*cit)->update();
}

void scene::draw()
{
	for( auto cit = entities.cbegin(); cit != entities.cend(); ++cit )
		(*cit)->draw();
}

void scene::add( entity *ent )
{
	ent->id = entity_id_counter++;
	std::cout << "Creating " << ent->tag << " with id " << ent->id << std::endl;
	entities.push_back( std::shared_ptr<entity>( ent ));
}

