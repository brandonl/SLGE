#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <unordered_map>
#include "Font.h"
#include "Texture.h"
#include "Utils.h"

namespace slge
{
	class Resources : private Uncopyable
	{
		public:
			typedef std::shared_ptr<Resource*> ResPtr;

		public:
			Resources();
			~Resources();

			void init();

			static void			setWorkingDir( const std::string& dir );
			static ResPtr*	grab( const std::string& filename );

		private:
			bool add( Resource *res );
			Resource* requestFromFilename( const std::string &filename );

		private:
			std::unordered_map< std::string, ResPtr > resourceMap;
			std::string workingDirectory;

			static Resources* instance;
	};
};


#endif
