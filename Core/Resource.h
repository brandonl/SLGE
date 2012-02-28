#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

namespace slge
{
	class Resource
	{
		protected:
			Resource( std::string fn = "" ) : filename(fn)
			{};

			virtual ~Resource() = 0;

			std::string filename;
			friend class Resources;
	};
};
#endif
