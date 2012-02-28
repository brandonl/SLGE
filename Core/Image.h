#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <memory>
#include <functional>

#include "Resource.h"
#include "Utils.h"
#include "stb_image.hpp"

namespace slge
{
	class Image : public Resource, private Uncopyable
	{
		public:
			Image( const std::string filename )
				:	Resource( filename ),
					raw( stbi_load( filename.c_str(), &width, &height, nullptr, 4 ), stbi_image_free )
			{
			}

			Image& operator=( Image&& m )
			{
				width = std::move( m.width );
				height = std::move( m.height );
				raw.swap( m.raw );
				return *this;
			}

		private:
			int width, height;
			std::unique_ptr< unsigned char, std::function<void(unsigned char*)> > raw;
	};
};

#endif