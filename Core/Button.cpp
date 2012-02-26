#include <iostream>
#include "Button.h"
#include "Input.h"

using namespace slge;

Button::Button( const std::string &text, Font *f, const glm::vec2 &center, const Color& col, float w, float h )
	:	center(center),
		width(w),
		height(h),
		visible(true),
		hot(false),
		clicked(false)
{
	tag = Label( text, f, center, col );
	if( width < 0.0f || height < 0.0f )
	{
		width = tag.getWidth();
		height = tag.getHeight();
	}
}

Button::~Button()
{
}

void Button::draw() const
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

bool Button::update()
{
	glm::vec2 mp( Input::getMousePosition().x, Input::getMousePosition().y  );
	hot = false;
	clicked = false;

	if( mp.x > ( center.x - width/2.0f ) && mp.x < ( center.x + width/2.0f ) && mp.y > ( center.y - height/2.0f ) && mp.y < ( center.y + height/2.0f ) )
		hot = true;

	if( Input::isMouseButtonPressed( Input::MOUSE_LEFT ) && hot )
		clicked = true;

	return clicked;
}

bool Button::isClicked() const
{
	return clicked;
}

bool Button::isHot() const
{
	return hot;
}
