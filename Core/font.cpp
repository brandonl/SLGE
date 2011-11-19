#include <windows.h>
#include <gl/gl.h>
#include "font.h"

// This define "expands out the actual implemenation into this file.
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"
#include <iostream>

using namespace slge;

font::font()
	:	resource(),
		pixel_height(0.0f),
		texture_height(512),
		texture_width(512)
{
}

font::~font()
{
	std::cout << "Deleting font" << std::endl;
	glDeleteTextures( 1, &texid );
	if( cdata )
		delete cdata;
}

// Code based on stb_ttf usage examples.
bool font::load( const std::string &fp, float pixel_height, unsigned int tex_width, unsigned int tex_height )
{
	FILE *ptr_file = fopen( fp.c_str(), "rb" );
	if( ptr_file == NULL )
	{
		std::cerr << "font::load: Error: font file failed to open.\n";
		return false;
	}

	filename = fp;
	unsigned char* buffer = new unsigned char [1<<20];
	fread( buffer, 1, 1<<20, ptr_file );
	fclose( ptr_file );

	this->pixel_height = pixel_height;

	if( tex_width != 0 )
		texture_width = tex_width;

	if( tex_height != 0 )
		texture_width = tex_width;

	// ASCII 32..126 is 95 glyphs
	cdata = new stbtt_bakedchar[96];
	unsigned char* bitmap = new unsigned char[ texture_width*texture_height ];
	if( ( stbtt_BakeFontBitmap( buffer, 0, this->pixel_height, bitmap, texture_width, texture_height, 32, 96, (stbtt_bakedchar *)cdata ) == 0 ) )
	{
		std::cerr << "font::load: Error: No characters fit and no rows were used.\n";
		delete buffer;
		delete bitmap;
		return false;
	}
	delete buffer;

	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &texid );
	glBindTexture( GL_TEXTURE_2D, texid );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, texture_width, texture_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	delete bitmap;

	loaded = true;
	glDisable( GL_TEXTURE_2D );
	return true;
}

font::glyph_data font::get_glyph_data( char c, float *x, float *y ) const
{
	glyph_data quad;
	stbtt_GetBakedQuad( (stbtt_bakedchar *)cdata, texture_width, texture_height, c - 32, x, y, (stbtt_aligned_quad *)&quad, 1 );
	return quad;
}

void font::use() const
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, texid );
}

void font::toss() const
{
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable( GL_TEXTURE_2D );
}