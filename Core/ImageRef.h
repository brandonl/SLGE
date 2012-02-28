#ifndef __IMAGE_REF_H__
#define __IMAGE_REF_H__

#include "Image.h"
#include "ResourceModule.h"
#include <iostream>

namespace slge
{
	class ImageRef
	{
		public:
			explicit ImageRef( const std::string& filename = "" )
			{
				if( filename.size() )
					Resources::request( filename, image );
			}

			ImageRef( ImageRef&& m )
				:	image( std::move( m.image ) )
			{
			}

			ImageRef& operator=( ImageRef&& m )
			{
				image.swap( m.image );
				return *this;
			}

		private:
			std::shared_ptr< Image > image;
	};
};

#endif