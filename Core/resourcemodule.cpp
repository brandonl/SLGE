#include "resourcemodule.h"
#include <iostream>

using namespace slge;

resources *resources::instance = NULL;

resources::resources()
{
	if( instance != NULL )
		std::cerr << "Only one resource module allowed.\n";;

	instance = this;
}

resources::~resources()
{
	std::for_each( resource_map.begin(), resource_map.end(), delete_map_functor() );
	resource_map.clear();
}

void resources::init()
{
	set_working_dir();
}

void resources::set_working_dir( const std::string& dir )
{
	instance->working_directory = dir;
}

texture* resources::grab_texture( const std::string& filename )
{
	if( filename.empty() )
	{
		std::cerr << "The resource with filename: " << filename << " does not exist.\n";
		return 0;
	}

	std::string filename_and_path = instance->working_directory + filename;

	texture *res = static_cast<texture*>( instance->request_from_filename( filename_and_path ) );

	if( !res )
	{
		res = new texture();
		if( !res->load( filename_and_path ) )
		{
			std::cerr << "Failed to load resource with filename " << filename << std::endl;;
			delete res;
			res = 0;
			return 0;
		}

		if( !instance->add( res ) )
		{
			std::cerr << "Failed to add resource to cache with filename: " << filename << std::endl;
			return 0;
		}
		//else
		//	std::cout << "Resource added with filename: " << filename << std::endl;
	}

	//else
	//	std::cout << "Resource is already cached with filename: " << filename << std::endl;

	return res;
}

font* resources::grab_font(	const std::string &filename, float pixel_height, int tex_width, int tex_height )
{
	if( filename.empty() )
	{
		std::cerr << "The resource with filename: " << filename << " does not exist.\n";
		return 0;
	}

	std::string filename_and_path = instance->working_directory + filename;

	font *res = static_cast<font*>( instance->request_from_filename( filename_and_path ) );

	if( !res )
	{
		res = new font();
		if( !res->load( filename_and_path, pixel_height, tex_width, tex_height ) )
		{
			std::cerr << "Failed to load resource with filename " << filename << std::endl;;
			delete res;
			res = 0;
			return 0;
		}

		if( !instance->add( res ) )
		{
			std::cerr << "Failed to add resource to cache with filename: " << filename << std::endl;
			return 0;
		}
		//else
		//	std::cout << "Resource added with filename: " << filename << std::endl;
	}

	else
	{
		if( res->pixel_height == pixel_height )
			std::cerr << "Resource is already cached with filename: " << filename << std::endl;
		else
		{
			res = new font();
			if( !res->load( filename_and_path, pixel_height, tex_width, tex_height ) )
			{
				std::cerr << "Failed to load resource with filename " << filename << std::endl;;
				delete res;
				res = 0;
				return 0;
			}

			if( !instance->add( res ) )
			{
				std::cerr << "Failed to add resource to cache with filename: " << filename << std::endl;
				return 0;
			}
			//else
			//	std::cout << "Resource added with filename: " << filename << " and pixel size: " << res->pixel_height << std::endl;
		}
	}

	return res;
}

bool resources::add( resource *res )
{
	if( !res->loaded )
		return false;

	static unsigned int id = -1;
	res->id = static_cast< int >( id++ );

	resource_map[ res->filename ] = res;
	return true;
}

resource* resources::request_from_filename( const std::string &filename )
{
	if( filename.empty() )
		return NULL;

	for( auto map_it = resource_map.cbegin(); map_it != resource_map.cend(); ++map_it )
	{
		if( ( ( *map_it ).second )->filename == filename )
			return ( ( *map_it ).second );
	}

	return NULL;
}
