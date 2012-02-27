#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>

namespace slge
{
	class Resource
	{
		protected:
			Resource( std::string fn = "" ) : filename(fn), loaded(false) { std::cout << "created resource: " << fn << std::endl; };
			virtual ~Resource() = 0;

			std::string filename;
			bool loaded;
			unsigned int id;

			friend class Resources;
	};
};
#endif
