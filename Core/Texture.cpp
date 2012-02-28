#include "Texture.h"
#include <cstdio>
#include "ImageRef.h"

using namespace slge;

Texture::~Texture()
{
	glDeleteTextures( 1, &name );
}

bool Texture::load( const ImageRef &iref )
{
	if( !iref ) return false;

	width = iref.getImageWidth();
	height = iref.getImageHeight();

	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &name );
	glBindTexture( GL_TEXTURE_2D, name );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGBA, 
						width, height, 0, GL_RGBA, 
						GL_UNSIGNED_BYTE,
						iref.referencedData() 
					);

	glDisable( GL_TEXTURE_2D );
	return true;
}
