#include <iostream>
#include "button.h"
#include "input.h"

using namespace slge;

button::button( const std::string &text, font *f, const b2Vec2 &center, const color& col, float w, float h )
	:	center(center),
		width(w),
		height(h),
		visible(true),
		hot(false),
		clicked(false)
{
	tag = label( text, f, center, col );
	if( width < 0.0f || height < 0.0f )
	{	
		width = tag.get_width();
		height = tag.get_height();
	}
}

button::~button()
{
}

void button::draw() const
{
	if( visible )
	{	
		/*if( hot )
		{
			glEnable( GL_BLEND );
			glPushMatrix();
			glTranslatef( center.x - width/2.0, center.y + height/2.0f, 0.0f );
			glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
			glBegin( GL_QUADS );
				glVertex2f( lbl.aabb.ux,			lbl.aabb.uy );
				glVertex2f( lbl.aabb.ux + width,	lbl.aabb.uy );
				glVertex2f( lbl.aabb.ux + width,	lbl.aabb.uy + height  );
				glVertex2f( lbl.aabb.ux,			lbl.aabb.uy + height );
			glEnd();
			glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
			glPopMatrix();
			glDisable( GL_BLEND );
		}*/

		tag.draw();
	}
}

bool button::update()
{
	b2Vec2 mp( input::get_mouse_position().x, input::get_mouse_position().y  );
	hot = false;
	clicked = false;

	if( mp.x > ( center.x - width/2.0f ) && mp.x < ( center.x + width/2.0f ) && mp.y > ( center.y - height/2.0f ) && mp.y < ( center.y + height/2.0f ) )
		hot = true;

	if( input::is_mouse_button_pressed( input::MOUSE_LEFT ) && hot )
		clicked = true;

	return clicked;
}

bool button::is_clicked() const
{
	return clicked;
}

bool button::is_hot() const
{
	return hot;
}