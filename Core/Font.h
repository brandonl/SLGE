#ifndef FONT_H
#define FONT_H

#include "Resource.h"
#include <string>
#include "Utils.h"
#include <memory>

namespace slge
{
	class Font : public Resource, private Uncopyable
	{
		public:
			struct glyphData;

			Font( const std::string &fp );
			Font& Font::operator=( Font&& m );

			const void*			getBitmapData() const;
			const void*			getCharData() const;
			const glyphData	getGlyphData( char c, float *x, float *y ) const;

		private:
			std::unique_ptr< unsigned char > charData;
			std::unique_ptr< unsigned char > bitmap;

		public:
			struct glyphData
			{
			   float ulx, uly, uls, ult; // top-left
			   float lrx, lry, lrs, lrt; // bottom-right
			};
	};

	inline const void* Font::getBitmapData() const
	{
		return bitmap.get();
	}

	inline const void* Font::getCharData() const
	{
		return charData.get();
	}
};

#endif
