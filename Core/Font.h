#ifndef FONT_H
#define FONT_H

#include "Resource.h"
#include <string>
#include <memory>
#include "Settings.h"

namespace slge
{
	class Font : public Resource
	{
		public:
			struct glyphData;

			Font( const std::string &fp, float pixHeight = TTF_DEFAULT_PIXEL_HEIGHT );
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
			   float ulx, uly, uls, ult;
			   float lrx, lry, lrs, lrt;
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
