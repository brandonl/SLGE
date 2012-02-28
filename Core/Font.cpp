#include "Font.h"
// This define "expands out the actual implemenation into this file.
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include "Settings.h"

using namespace slge;

Font::Font( const std::string &fn )
	:	Resource( fn )
{
	std::ifstream tffFile( fn.c_str(), std::ios::binary );

	if( !tffFile.is_open() )
		printf( "Error: TTF Font file %s failed to open.\n", fn.c_str() );

	else
	{
		std::stringstream buffer;
		buffer << tffFile.rdbuf();

		// ASCII 32..126 is 95 glyphs
		charData.reset( new unsigned char[ sizeof stbtt_bakedchar * 96] );
		bitmap.reset( new unsigned char[ TTF_FONT_WIDTH * TTF_FONT_HEIGHT ] );

		if( ( stbtt_BakeFontBitmap(	// Pretty casts...."_"
												reinterpret_cast<const unsigned char*>( buffer.str().c_str() ), 0, 
												TTF_DEFAULT_PIXEL_HEIGHT, bitmap.get(), TTF_FONT_WIDTH, TTF_FONT_HEIGHT, 32, 96,
												reinterpret_cast<stbtt_bakedchar *>( charData.get() ) ) == 0 
											) )
			printf( "Error: No characters fit and no rows were used. TTF file: %s \n", fn.c_str() );
	}
}

Font& Font::operator=( Font&& m )
{
	charData.swap( m.charData );
	bitmap.swap( m.bitmap );
	return *this;
}

const Font::glyphData Font::getGlyphData( char c, float *x, float *y ) const
{
	glyphData quad;
	stbtt_GetBakedQuad(	reinterpret_cast<stbtt_bakedchar *>( charData.get() ), 
								TTF_FONT_WIDTH, TTF_FONT_HEIGHT, c - 32, x, y, 
								reinterpret_cast<stbtt_aligned_quad *>( &quad ), 1 
							);
	return quad;
}
