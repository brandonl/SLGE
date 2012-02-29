#ifndef __FONT_REF_H__
#define __FONT_REF_H__

#include "Font.h"
#include "ResourceModule.h"

namespace slge
{
	class FontRef
	{
		public:
			explicit FontRef( const std::string& fn = "" )
			{
				printf( "New fontref\n" );
				if( fn.size() )
					Resources::request( fn, font );
			}

			FontRef( FontRef&& m )
				:	font( std::move( m.font ) )
			{
			}

			FontRef& operator=( FontRef&& m )
			{
				font.swap( m.font );
				return *this;
			}

			operator bool() const
			{
				return static_cast<bool>( font );
			}

			const void*					referencedCharData() const;
			const void*					referencedBitmapData() const;
			const Font::glyphData	getGlyphData( char c, float *x, float *y ) const;
			const std::string			getFontName() const;

		private:
			std::shared_ptr< Font > font;
	};

	inline const void* FontRef::referencedBitmapData() const
	{
		return font->getBitmapData();
	}

	inline const void* FontRef::referencedCharData() const
	{
		return font->getCharData();
	}

	inline const Font::glyphData FontRef::getGlyphData( char c, float *x, float *y  ) const
	{
		return font->getGlyphData( c , x, y );
	}

	inline const std::string FontRef::getFontName() const
	{
		return font->getFileName();
	}
};

#endif