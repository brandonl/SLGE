#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <unordered_map>
#include "Utils.h"
#include <memory>

namespace slge
{
	class Resource;

	class Resources : private Uncopyable
	{
		public:
			Resources();
			~Resources(){}

			template <class T>
			static void	request( const std::string& filename, std::shared_ptr<T> &rsrc );
			static void	setWorkingDir( const std::string& path );

		private:
			std::unordered_map< std::string, std::shared_ptr<Resource> > cache;
			std::string workingDirectory;

			static Resources* instance;
	};

	template <class T>
	void Resources::request( const std::string& filename, std::shared_ptr<T> &rsrc )
	{
		auto ix = instance->cache.find( filename );

		if( ix != instance->cache.end() ) //Found
			rsrc = std::dynamic_pointer_cast<T>( ix->second );

		else //Not found in cache
		{
			rsrc = std::make_shared<T>( std::string( instance->workingDirectory ) + filename );
			instance->cache.emplace( std::make_pair( filename, rsrc ) );
		}
	}

	inline void Resources::setWorkingDir( const std::string& dir )
	{
		instance->workingDirectory = dir;
	}
};


#endif
