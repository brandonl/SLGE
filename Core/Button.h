#ifndef BUTTON_H
#define BUTTON_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "Font.h"
#include <string>

#include "Vertex.h"
#include "Label.h"
#include <vector>

namespace slge
{
	class Button
	{
		public:
			explicit Button() {};
			// Keep width and height -1 if you want the Button to be the exact width of the text string (Label)...
			explicit Button( const std::string &text, Font *f, const glm::vec2 &center, const Color& col = Color(), float width = -1, float height = -1 );
			~Button();

			void draw() const;
			bool update();
			bool isClicked() const;
			bool isHot() const;

			Label tag;
			glm::vec2 center;
			//std::vector<Vertex> vertices;
			float width;
			float height;
			bool visible;
			bool clicked;
			bool hot;
	};
};

#endif
