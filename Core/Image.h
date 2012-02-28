#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <memory>
#include <functional>
#include "Resource.h"
#include "Utils.h"

namespace slge
{
	class Image : public Resource, private Uncopyable
	{
		public:
			Image( const std::string& fn );
			Image& operator=( Image&& m );

			const void* getData() const;
			const int getWidth() const;
			const int getHeight() const;

		private:
			int width, height;
			std::unique_ptr< unsigned char, std::function<void(unsigned char*)> > raw;
	};

	inline const void* Image::getData() const
	{
		return raw.get();
	}

	inline const int Image::getWidth() const
	{ 
		return width;
	}

	inline const int Image::getHeight() const
	{
		return height;
	}
};

#endif