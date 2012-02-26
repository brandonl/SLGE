#include "ResourceModule.h"
#include <iostream>

using namespace slge;

Resources *Resources::instance = NULL;

Resources::Resources()
{
	if( instance != NULL )
		std::cerr << "Only one Resource module allowed.\n";;

	instance = this;
}

Resources::~Resources()
{
	std::for_each( resourceMap.begin(), resourceMap.end(), deleteMapFunctor() );
	resourceMap.clear();
}

void Resources::init()
{
	setWorkingDir();
}

void Resources::setWorkingDir( const std::string& dir )
{
	instance->workingDirectory = dir;
}

Texture* Resources::grabTexture( const std::string& filename )
{
	if( filename.empty() )
	{
		std::cerr << "The Resource with filename: " << filename << " does not exist.\n";
		return 0;
	}

	std::string filenameAndPath = instance->workingDirectory + filename;

	Texture *res = static_cast<Texture*>( instance->requestFromFilename( filenameAndPath ) );

	if( !res )
	{
		res = new Texture();
		if( !res->load( filenameAndPath ) )
		{
			std::cerr << "Failed to load Resource with filename " << filename << std::endl;;
			delete res;
			res = 0;
			return 0;
		}

		if( !instance->add( res ) )
		{
			std::cerr << "Failed to add Resource to cache with filename: " << filename << std::endl;
			return 0;
		}
		//else
		//	std::cout << "Resource added with filename: " << filename << std::endl;
	}

	//else
	//	std::cout << "Resource is already cached with filename: " << filename << std::endl;

	return res;
}

Font* Resources::grabFont(	const std::string &filename, float pixelHeight, int texWidth, int texHeight )
{
	if( filename.empty() )
	{
		std::cerr << "The Resource with filename: " << filename << " does not exist.\n";
		return 0;
	}

	std::string filenameAndPath = instance->workingDirectory + filename;

	Font *res = static_cast<Font*>( instance->requestFromFilename( filenameAndPath ) );

	if( !res )
	{
		res = new Font();
		if( !res->load( filenameAndPath, pixelHeight, texWidth, texHeight ) )
		{
			std::cerr << "Failed to load Resource with filename " << filename << std::endl;;
			delete res;
			res = 0;
			return 0;
		}

		if( !instance->add( res ) )
		{
			std::cerr << "Failed to add Resource to cache with filename: " << filename << std::endl;
			return 0;
		}
		//else
		//	std::cout << "Resource added with filename: " << filename << std::endl;
	}

	else
	{
		if( res->pixelHeight == pixelHeight )
			std::cerr << "Resource is already cached with filename: " << filename << std::endl;
		else
		{
			res = new Font();
			if( !res->load( filenameAndPath, pixelHeight, texWidth, texHeight ) )
			{
				std::cerr << "Failed to load Resource with filename " << filename << std::endl;;
				delete res;
				res = 0;
				return 0;
			}

			if( !instance->add( res ) )
			{
				std::cerr << "Failed to add Resource to cache with filename: " << filename << std::endl;
				return 0;
			}
			//else
			//	std::cout << "Resource added with filename: " << filename << " and pixel size: " << res->pixelHeight << std::endl;
		}
	}

	return res;
}

bool Resources::add( Resource *res )
{
	if( !res->loaded )
		return false;

	static unsigned int id = -1;
	res->id = static_cast< int >( id++ );

	resourceMap[ res->filename ] = res;
	return true;
}

Resource* Resources::requestFromFilename( const std::string &filename )
{
	if( filename.empty() )
		return NULL;

	for( auto mapIt = resourceMap.cbegin(); mapIt != resourceMap.cend(); ++mapIt )
	{
		if( ( ( *mapIt ).second )->filename == filename )
			return ( ( *mapIt ).second );
	}

	return NULL;
}
