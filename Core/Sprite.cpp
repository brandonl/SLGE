#include "Sprite.h"
#include "Settings.h"
#include "Texture2D.h"
#include <algorithm>
#include <functional>

using namespace slge;

//--------------------------------------------------------------Animated Sprite :: Animation-------

AnimatedSprite::Animation::Animation( const std::string &name, unsigned int start, unsigned int end, unsigned int level, float speed )
	:	name(name),
		frame(start),
		start(start),
		end(end),
		level(level),
		speed(speed),
		lastUpdate(0.f)
{
}

//--------------------------------------------------------------------Animated Sprite-------------

void AnimatedSprite::doUpdate()
{
	if( isVisible() )
	{
		if( currentAnim )
		{
			currentAnim->lastUpdate += static_cast<float>( DELTA_TIME );
			if( currentAnim->lastUpdate < ( 1.0f / currentAnim->speed ) )
				return;

			++currentAnim->frame;
			if( currentAnim->frame > currentAnim->end )
				currentAnim->frame = currentAnim->start;

			int x = static_cast<int>( currentAnim->frame ) % 
											(	( textureSheet.getHWidth() << 1 ) / 
												( hwidth << 1 ) );
			int y = currentAnim->level;
			texOffset = glm::vec2(	( x * hwidth * 2.f ) / 
											( textureSheet.getHWidth() << 1 ),
											( y * hheight * 2.f ) / 
											( textureSheet.getHHeight() << 1 ) 
										 );

			quad[0].texCoord[0] = texOffset.x;					
			quad[0].texCoord[1] = texOffset.y;
			quad[1].texCoord[0] = texOffset.x + texScale.x;	
			quad[1].texCoord[1] = texOffset.y;
			quad[2].texCoord[0] = texOffset.x + texScale.x;	
			quad[2].texCoord[1] = texOffset.y + texScale.y;
			quad[3].texCoord[0] = texOffset.x;					
			quad[3].texCoord[1] = texOffset.y + texScale.y;
			currentAnim->lastUpdate = 0;
		}
	}
}

void AnimatedSprite::add(	const std::string &anim, unsigned int start, 
									unsigned int end, unsigned int level, float speed 
								)
{
	anims.push_back( Animation( anim, start, end, level, speed ) );
}

void AnimatedSprite::play( const std::string &anim )
{
	currentAnim = get( anim );
}

void AnimatedSprite::stop( const std::string &anim )
{
	currentAnim = 0;
}

AnimatedSprite::Animation *AnimatedSprite::get( const std::string &anim )
{
	auto ix = std::find_if( anims.begin(), anims.end(), 
									[&]( const Animation &s ) -> bool
									{
										return s.name == anim;
									} 
								);
	if( ix == anims.end() )
		return nullptr;

	return &(*ix);
}

//--------------------------------------------------------------------------Sprite-------------
float clamp( float num, float min, float max )
{
	return ( num < min ) ? min : ( num > max ) ? max : num;
}

Sprite::Sprite( const Texture2 &textureSheet, int width, int height, const Color& col )
	:	textureSheet( textureSheet ),
		hwidth(width >> 1),
		hheight(height >> 1),
		visible(true)
{
	if( width < 0 ) hwidth = textureSheet.getHWidth();
	if( height < 0 ) hheight = textureSheet.getHHeight();
	texOffset = glm::vec2( 0.0f, 0.0f );
	texScale = glm::vec2(	1.f * width  / ( textureSheet.getHWidth() << 1  ), 
									1.f * height / ( textureSheet.getHHeight() << 1 ) );
	if( width < 0 ) texScale.x = 1.f;
	if( height < 0 ) texScale.y = 1.f;

	quad.reserve(4);
	quad.emplace_back( Vertex( -hwidth,	-hheight, texOffset.x,					texOffset.y,					col ) );
	quad.emplace_back( Vertex(  hwidth,	-hheight, texOffset.x + texScale.x, texOffset.y,					col ) );
	quad.emplace_back( Vertex(  hwidth,	 hheight, texOffset.x + texScale.x,	texOffset.y + texScale.y,	col ) );
	quad.emplace_back( Vertex( -hwidth,	 hheight, texOffset.x,					texOffset.y + texScale.y,	col ) );
}

void Sprite::doDraw() const
{
	if( isVisible() )
	{
		glEnable( GL_BLEND );
		textureSheet.bind();

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer( 2, GL_FLOAT, sizeof(Vertex), &quad[0].position );
		glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &quad[0].texCoord );
		glColorPointer( 4, GL_FLOAT, sizeof(Vertex), &quad[0].vColor );
		glDrawArrays( GL_QUADS, 0, 4 );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		textureSheet.unbind();
		glDisable( GL_BLEND );
	}
}