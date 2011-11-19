#include "sprite.h"
#include <iostream>
#include "world.h"

using namespace slge;

sprite::animation::animation( const std::string &name, unsigned int start, unsigned int end, unsigned int level, float speed )
	:	name(name),
		frame(start),
		start(start),
		end(end),
		level(level),
		speed(speed),
		last_update(0.0f)
{
}

sprite::sprite( const std::string& path, float w, float h, int tw, int th, const color& col )
	:	width(w),
		height(h),
		tw(tw),
		th(th),
		visible(true),
		vertices( 4 ),
		anims( 4 ),
		current_anim(0)
{
	sheet = resources::grab_texture( path );
	tex_offset = vec2( 0.0f, 0.0f );
	tex_scale = vec2( width/tw, height/th );
	float halfw = get_hwidth();
	float halfh = get_hheight();
	vertices[0] = vertex( -halfw,	-halfh,	tex_offset.x,				tex_offset.y,				col );
	vertices[1] = vertex( halfw,	-halfh,	tex_offset.x + tex_scale.x, tex_offset.y,				col );
	vertices[2] = vertex( halfw,	halfh, tex_offset.x + tex_scale.x,	tex_offset.y + tex_scale.y,	col );
	vertices[3] = vertex( -halfw,	halfh, tex_offset.x,				tex_offset.y + tex_scale.y, col );
}

sprite::~sprite()
{
}

void sprite::draw()
{
	if( visible )
	{	
		glEnable( GL_BLEND );
		sheet->bind();

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer( 2, GL_FLOAT, sizeof(vertex), &vertices[0].position );
		glTexCoordPointer( 2, GL_FLOAT, sizeof(vertex), &vertices[0].texcoord );
		glColorPointer( 4, GL_FLOAT, sizeof(vertex), &vertices[0].vcolor );
		glDrawArrays( GL_QUADS, 0, 4 );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		sheet->unbind();
		glDisable( GL_BLEND );
	}
}

void sprite::update()
{
	if( visible )
	{
		if( current_anim )
		{
			current_anim->last_update += DELTA_TIME;
			if( current_anim->last_update < ( 1.0f / current_anim->speed ) )
				return;

			++current_anim->frame;
			if( current_anim->frame > current_anim->end )
				current_anim->frame = current_anim->start;

			int x = (int)current_anim->frame % (int)( tw / ( width ) );
			int y = current_anim->level;
			tex_offset = vec2( ( x * width ) / tw, ( y * height ) / th );

			vertices[0].texcoord[0] = tex_offset.x;					vertices[0].texcoord[1] = tex_offset.y;
			vertices[1].texcoord[0] = tex_offset.x + tex_scale.x;	vertices[1].texcoord[1] = tex_offset.y;
			vertices[2].texcoord[0] = tex_offset.x + tex_scale.x;	vertices[2].texcoord[1] = tex_offset.y + tex_scale.y;
			vertices[3].texcoord[0] = tex_offset.x;					vertices[3].texcoord[1] = tex_offset.y + tex_scale.y;
			current_anim->last_update = 0;
		}
	}
}

void sprite::add( const std::string &anim, unsigned int start, unsigned int end, unsigned int level, float speed )
{
	anims.push_back( animation( anim, start, end, level, speed ) );
}

void sprite::play( const std::string &anim )
{
	current_anim = get( anim );
}

void sprite::stop( const std::string &anim )
{
	current_anim = 0;
}

sprite::animation *sprite::get( const std::string &anim )
{
	for( std::list<animation>::iterator i = anims.begin(); i != anims.end(); ++i )
	{
		if( i->name == anim )
		{
			return &(*i);
		}
	}

	std::cerr <<  "No animation with the name: " << anim << std::endl;
	return 0;
}

float sprite::get_hwidth() const
{
	return width / 2.0f;
}

float sprite::get_hheight() const
{
	return height / 2.0f;
}
