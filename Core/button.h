#ifndef BUTTON_H
#define BUTTON_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "font.h"
#include <string>
#include <Box2D.h>
#include "vertex.h"
#include "label.h"
#include <vector>

namespace slge
{
	class button
	{
		public:
			explicit button() {};
			// Keep width and height -1 if you want the button to be the exact width of the text string (label)...
			explicit button( const std::string &text, font *f, const b2Vec2 &center, const color& col = color(), float width = -1, float height = -1 );
			~button();

			void draw() const;
			bool update();
			bool is_clicked() const;
			bool is_hot() const;

			label tag;
			b2Vec2 center;
			//std::vector<vertex> vertices;
			float width;
			float height;
			bool visible;
			bool clicked;
			bool hot;
	};
};

#endif