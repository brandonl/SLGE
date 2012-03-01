#include "Texture2D.h"
#include <cstdio>

using namespace slge;

// TODO: Note Code duplication..
Texture2::Texture2( const ImageRef &&iref )
{
	printf( "Creating new texture form reference of file: %s.\n", iref.getImageName().c_str() );
	if( iref )
	{
		hwidth = iref.getImageWidth();
		hheight = iref.getImageHeight();

		glEnable( GL_TEXTURE_2D );
		glGenTextures( 1, &name );
		glBindTexture( GL_TEXTURE_2D, name );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGBA, 
							hwidth, hheight, 0, GL_RGBA, 
							GL_UNSIGNED_BYTE,
							iref.referencedData() 
						);

		hheight >>= 1;
		hwidth >>= 1;
		glDisable( GL_TEXTURE_2D );
	}
	else printf( "Failed to create Texture2 from ImageRef: %s", iref.getImageName().c_str() );
}

Texture2::Texture2( const std::string &imageFileName )
{
	ImageRef iref( imageFileName );
	printf( "Creating new texture form file: %s.\n", iref.getImageName().c_str() );
	if( iref )
	{
		hwidth = iref.getImageWidth();
		hheight = iref.getImageHeight();

		glEnable( GL_TEXTURE_2D );
		glGenTextures( 1, &name );
		glBindTexture( GL_TEXTURE_2D, name );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGBA, 
							hwidth, hheight, 0, GL_RGBA, 
							GL_UNSIGNED_BYTE,
							iref.referencedData() 
						);

		hheight >>= 1;
		hwidth >>= 1;
		glDisable( GL_TEXTURE_2D );
	}
	else printf( "Failed to create Texture2 from ImageRef: %s", iref.getImageName().c_str() );
}

Texture2::~Texture2()
{
	glDeleteTextures( 1, &name );
}

