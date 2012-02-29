#include "Text2D.h"
#include "Settings.h"
#include "Vertex.h"

using namespace slge;

Text2::Text2( const FontRef &fref )
{
	if( fref )
	{
		glEnable( GL_TEXTURE_2D );
		glGenTextures( 1, &name );
		glBindTexture( GL_TEXTURE_2D, name );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glTexImage2D(	GL_TEXTURE_2D, 0, GL_ALPHA, 
							TTF_FONT_WIDTH, TTF_FONT_HEIGHT, 0, GL_ALPHA, 
							GL_UNSIGNED_BYTE,
							fref.referencedBitmapData() 
						);

		glDisable( GL_TEXTURE_2D );

		precomputeFontFaces( fref );
	}
	else printf( "Failed to create Text2 object from FontRef: %s", fref.getFontName().c_str() );
}

Text2::~Text2()
{
	glDeleteTextures( 1, &name );
}

void Text2::precomputeFontFaces( const FontRef &fref )
{
	float x = 0.f, y = 0.f;
	int i = 0;
	for( char c = 32; c < 127; ++c )
	{
		Font::glyphData gQuad = fref.getGlyphData( c, &x, &y );
		precomputedSpatialGlyphs[ ( c - 32 ) ][0] = Vertex( gQuad.ulx, gQuad.uly, gQuad.uls, gQuad.ult );
		precomputedSpatialGlyphs[ ( c - 32 ) ][1] = Vertex( gQuad.lrx, gQuad.uly, gQuad.lrs, gQuad.ult );
		precomputedSpatialGlyphs[ ( c - 32 ) ][2] = Vertex( gQuad.lrx, gQuad.lry, gQuad.lrs, gQuad.lrt );
		precomputedSpatialGlyphs[ ( c - 32 ) ][3] = Vertex( gQuad.ulx, gQuad.lry, gQuad.uls, gQuad.lrt );
	}
}


void Text2::dynamicDrawString( const std::string& msg, float scale ) const
{
	glEnable( GL_BLEND );
	bind();
	glPushMatrix();
	glTranslatef( 10.f, 100.f, 0.f );
	glScalef( scale, scale, 0.f );
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer( 2, GL_FLOAT, sizeof(Vertex), &precomputedSpatialGlyphs[0][0].position );
		glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &precomputedSpatialGlyphs[0][0].texCoord );
		glColorPointer( 4, GL_FLOAT, sizeof(Vertex), &precomputedSpatialGlyphs[0][0].vColor );
		glDrawArrays( GL_QUADS, 0, precomputedSpatialGlyphs.size() * 4 );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
	unbind();
	glDisable( GL_BLEND );
}
