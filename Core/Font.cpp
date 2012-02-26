#include <windows.h>
#include <gl/gl.h>
#include "Font.h"

// This define "expands out the actual implemenation into this file.
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#include <iostream>

using namespace slge;

Font::Font()
	:	Resource(),
		pixelHeight(0.0f),
		textureHeight(512),
		textureWidth(512)
{
}

Font::~Font()
{
	std::cout << "Deleting Font" << std::endl;
	glDeleteTextures( 1, &texid );
	if( cdata )
		delete cdata;
}

// Code based on stbTtf usage examples.
bool Font::load( const std::string &fp, float pixelHeight, unsigned int texWidth, unsigned int texHeight )
{
	FILE *ptrFile = fopen( fp.c_str(), "rb" );
	if( ptrFile == NULL )
	{
		std::cerr << "Font::load: Error: Font file failed to open.\n";
		return false;
	}

	filename = fp;
	unsigned char* buffer = new unsigned char [1<<20];
	fread( buffer, 1, 1<<20, ptrFile );
	fclose( ptrFile );

	this->pixelHeight = pixelHeight;

	if( texWidth != 0 )
		textureWidth = texWidth;

	if( texHeight != 0 )
		textureWidth = texWidth;

	// ASCII 32..126 is 95 glyphs
	cdata = new stbtt_bakedchar[96];
	unsigned char* bitmap = new unsigned char[ textureWidth*textureHeight ];
	if( ( stbtt_BakeFontBitmap( buffer, 0, this->pixelHeight, bitmap, textureWidth, textureHeight, 32, 96, (stbtt_bakedchar *)cdata ) == 0 ) )
	{
		std::cerr << "Font::load: Error: No characters fit and no rows were used.\n";
		delete buffer;
		delete bitmap;
		return false;
	}
	delete buffer;

	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &texid );
	glBindTexture( GL_TEXTURE_2D, texid );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, textureWidth, textureHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	delete bitmap;

	loaded = true;
	glDisable( GL_TEXTURE_2D );
	return true;
}

Font::glyphData Font::getGlyphData( char c, float *x, float *y ) const
{
	glyphData quad;
	stbtt_GetBakedQuad( (stbtt_bakedchar *)cdata, textureWidth, textureHeight, c - 32, x, y, (stbtt_aligned_quad *)&quad, 1 );
	return quad;
}

void Font::use() const
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, texid );
}

void Font::toss() const
{
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable( GL_TEXTURE_2D );
}
