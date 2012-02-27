#include "Sprite.h"
#include <iostream>
#include "World.h"
#include "Defines.h"

using namespace slge;

Sprite::Animation::Animation( const std::string &name, unsigned int start, unsigned int end, unsigned int level, float speed )
	:	name(name),
		frame(start),
		start(start),
		end(end),
		level(level),
		speed(speed),
		lastUpdate(0.0f)
{
}

Sprite::Sprite( const std::string& path, float w, float h, int tw, int th, const Color& col )
	:	width(w),
		height(h),
		tw(tw),
		th(th),
		visible(true),
		vertices( 4 ),
		anims( 4 ),
		currentAnim(0)
{
	sheet = Resources::grabTexture( path );
	texOffset = glm::vec2( 0.0f, 0.0f );
	texScale = glm::vec2( width/tw, height/th );
	float halfw = getHwidth();
	float halfh = getHheight();
	vertices[0] = Vertex( -halfw,	-halfh,	texOffset.x,				texOffset.y,				col );
	vertices[1] = Vertex( halfw,	-halfh,	texOffset.x + texScale.x, texOffset.y,				col );
	vertices[2] = Vertex( halfw,	halfh, texOffset.x + texScale.x,	texOffset.y + texScale.y,	col );
	vertices[3] = Vertex( -halfw,	halfh, texOffset.x,				texOffset.y + texScale.y, col );
}

Sprite::~Sprite()
{
}

void Sprite::draw()
{
	if( visible )
	{
		glEnable( GL_BLEND );
		sheet->bind();

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer( 2, GL_FLOAT, sizeof(Vertex), &vertices[0].position );
		glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &vertices[0].texcoord );
		glColorPointer( 4, GL_FLOAT, sizeof(Vertex), &vertices[0].vcolor );
		glDrawArrays( GL_QUADS, 0, 4 );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		sheet->unbind();
		glDisable( GL_BLEND );
	}
}

void Sprite::update()
{
	if( visible )
	{
		if( currentAnim )
		{
			currentAnim->lastUpdate += DELTA_TIME;
			if( currentAnim->lastUpdate < ( 1.0f / currentAnim->speed ) )
				return;

			++currentAnim->frame;
			if( currentAnim->frame > currentAnim->end )
				currentAnim->frame = currentAnim->start;

			int x = (int)currentAnim->frame % (int)( tw / ( width ) );
			int y = currentAnim->level;
			texOffset = glm::vec2( ( x * width ) / tw, ( y * height ) / th );

			vertices[0].texcoord[0] = texOffset.x;					vertices[0].texcoord[1] = texOffset.y;
			vertices[1].texcoord[0] = texOffset.x + texScale.x;	vertices[1].texcoord[1] = texOffset.y;
			vertices[2].texcoord[0] = texOffset.x + texScale.x;	vertices[2].texcoord[1] = texOffset.y + texScale.y;
			vertices[3].texcoord[0] = texOffset.x;					vertices[3].texcoord[1] = texOffset.y + texScale.y;
			currentAnim->lastUpdate = 0;
		}
	}
}

void Sprite::add( const std::string &anim, unsigned int start, unsigned int end, unsigned int level, float speed )
{
	anims.push_back( Animation( anim, start, end, level, speed ) );
}

void Sprite::play( const std::string &anim )
{
	currentAnim = get( anim );
}

void Sprite::stop( const std::string &anim )
{
	currentAnim = 0;
}

Sprite::Animation *Sprite::get( const std::string &anim )
{
	for( std::list<Animation>::iterator i = anims.begin(); i != anims.end(); ++i )
	{
		if( i->name == anim )
		{
			return &(*i);
		}
	}

	std::cerr <<  "No Animation with the name: " << anim << std::endl;
	return 0;
}

float Sprite::getHwidth() const
{
	return width / 2.0f;
}

float Sprite::getHheight() const
{
	return height / 2.0f;
}
