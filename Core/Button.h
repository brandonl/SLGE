#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <string>
#include <glm/glm.hpp>

namespace slge
{
	template <class T>
	class Button // : public Entity
	{
		public:
			explicit Button( const T &&type, float padding = 0.f );
			~Button();

			void draw() const;
			bool update();
			bool isClicked() const;
			bool isHot() const;

		private:
			const T buttonType;
			glm::vec2 center;
			bool visible;
			bool clicked;
			bool hot;
			float padding;
	};

	template <class T>
	Button<T>::Button( const T &&type, float padding )
		:	buttonType(type),
			center(center),
			visible(true),
			hot(false),
			clicked(false),
			padding(padding)
	{
	}

	template <class T>
	Button<T>::~Button()
	{
	}

	template <class T>
	void Button<T>::draw() const
	{
		if( visible )
		{
			if( hot )
			{
				glEnable( GL_BLEND );
				glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
				glBegin( GL_QUADS );
				glVertex2f( buttonType.getCenter().x - buttonType.getHWidth() - padding,	buttonType.getCenter().y - buttonType.getHHeight() - padding );
				glVertex2f( buttonType.getCenter().x + buttonType.getHWidth() + padding,	buttonType.getCenter().y - buttonType.getHHeight() - padding  );
				glVertex2f( buttonType.getCenter().x + buttonType.getHWidth() + padding,	buttonType.getCenter().y + buttonType.getHHeight() + padding  );
				glVertex2f( buttonType.getCenter().x - buttonType.getHWidth() - padding,	buttonType.getCenter().y + buttonType.getHHeight() + padding  );
				glEnd();
				glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
				glDisable( GL_BLEND );
			}

			buttonType.draw();
		}
	}

	template <class T>
	bool Button<T>::update()
	{
		glm::vec2 mp( Input::getMousePosition().x, Input::getMousePosition().y  );
		hot = false;
		clicked = false;

		if(	mp.x > ( buttonType.getCenter().x - buttonType.getHWidth() - padding ) &&
				mp.x < ( buttonType.getCenter().x + buttonType.getHWidth() + padding ) && 
				mp.y > ( buttonType.getCenter().y - buttonType.getHHeight() - padding ) && 
				mp.y < ( buttonType.getCenter().y + buttonType.getHHeight() + padding ) 
			)
			hot = true;

		if( hot && Input::isMouseButtonPressed( Input::MOUSE_LEFT ) )
			clicked = true;

		return clicked;
	}

	template <class T>
	inline bool Button<T>::isClicked() const
	{
		return clicked;
	}

	template <class T>
	inline bool Button<T>::isHot() const
	{
		return hot;
	}
};

#endif
