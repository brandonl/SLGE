#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <map>
#include "Font.h"
#include "Texture.h"
#include "Utils.h"

namespace slge
{
	class Resources : public Uncopyable
	{
		public:
			explicit Resources();
			~Resources();
			void init();

			static void		setWorkingDir( const std::string& dir = "../../Resources/" );
			static Texture* grabTexture( const std::string& filename );
			static Font*	grabFont(	const std::string &filename, float size = 12.0f, int texWidth = 0, int texHeight = 0 );
			static void		removeAll();
			static void		remove( const std::string& filename );

		private:
			bool add( Resource *res );
			Resource* requestFromFilename( const std::string &filename );

			std::map< std::string, Resource* > resourceMap;
			std::string workingDirectory;
			static Resources* instance;
	};
};


#endif
