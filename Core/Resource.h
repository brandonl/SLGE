#ifndef RESOURCE_H
#define RESOURCE_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <string>
#include <map>

namespace slge
{
	class Resource
	{
		public:
			explicit Resource() : loaded(false) {};
			virtual ~Resource() = 0;

			std::string filename;
			bool loaded;
			unsigned int id;
	};
};
#endif
