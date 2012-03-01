#include "Text2D.h"
#include "Settings.h"
#include "Vertex.h"

using namespace slge;

Text2::Text2( const FontRef &&fref )
	:	fref( fref )
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
	}
	else printf( "Failed to create Text2 object from FontRef: %s", fref.getFontName().c_str() );
}

Text2::~Text2()
{
	glDeleteTextures( 1, &name );
}

const VertList Text2::buildStaticString( const std::string& msg, glm::vec2 pos, const Color& col, float size ) const
{
	static float scale = 1.f;
	if( size )
		scale = TTF_DEFAULT_PIXEL_HEIGHT/size;
	glScalef( scale, scale, 0.f );

	VertList vertsTmp;
	vertsTmp.reserve( msg.size() * 4 );

	for( auto cx = msg.begin(); cx != msg.end(); ++cx )
	{
      if( *cx >= 32 && *cx < 128 )
		{
			Font::glyphData gQuad = fref.getGlyphData( *cx, &pos.x, &pos.y );
			vertsTmp.emplace_back( Vertex( gQuad.ulx * scale, gQuad.uly * scale, gQuad.uls, gQuad.ult, col ) );
			vertsTmp.emplace_back( Vertex( gQuad.lrx * scale, gQuad.uly * scale, gQuad.lrs, gQuad.ult, col ) );
			vertsTmp.emplace_back( Vertex( gQuad.lrx * scale, gQuad.lry * scale, gQuad.lrs, gQuad.lrt, col ) );
			vertsTmp.emplace_back( Vertex( gQuad.ulx * scale, gQuad.lry * scale, gQuad.uls, gQuad.lrt, col ) );
      }
	}
	return vertsTmp;
}

void Text2::immediateDrawString( const std::string& msg, glm::vec2 pos, const Color& col, float size ) const
{
	static float scale = 1.f;
	if( size )
		scale = TTF_DEFAULT_PIXEL_HEIGHT/size;
	glScalef( scale, scale, 0.f );

	VertList vertsTmp;
	vertsTmp.reserve( msg.size() * 4 );

	for( auto cx = msg.begin(); cx != msg.end(); ++cx )
	{
      if( *cx >= 32 && *cx < 128 )
		{
			Font::glyphData gQuad = fref.getGlyphData( *cx, &pos.x, &pos.y );
			vertsTmp.emplace_back( Vertex( gQuad.ulx * scale, gQuad.uly * scale, gQuad.uls * scale, gQuad.ult, col ) );
			vertsTmp.emplace_back( Vertex( gQuad.lrx * scale, gQuad.uly * scale, gQuad.lrs * scale, gQuad.ult, col ) );
			vertsTmp.emplace_back( Vertex( gQuad.lrx * scale, gQuad.lry * scale, gQuad.lrs * scale, gQuad.lrt, col ) );
			vertsTmp.emplace_back( Vertex( gQuad.ulx * scale, gQuad.lry * scale, gQuad.uls * scale, gQuad.lrt, col ) );
      }
   }

	glEnable( GL_BLEND );
	bind();
	glPushMatrix();

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );

	glVertexPointer( 2, GL_FLOAT, sizeof(Vertex), &vertsTmp[0].position );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &vertsTmp[0].texCoord );
	glColorPointer( 4, GL_FLOAT, sizeof(Vertex), &vertsTmp[0].vColor );

	glDrawArrays( GL_QUADS, 0, vertsTmp.size() );

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
	unbind();
	glDisable( GL_BLEND );
}
