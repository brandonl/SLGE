#ifndef LABEL_H
#define LABEL_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "font.h"
#include <string>
#include <Box2D.h>
#include "color.h"
#include <vector>
#include "vertex.h"
#include "rect.h"

namespace slge
{
	class label
	{
		public:
			explicit label() {};
			explicit label( const std::string &text, font *f, const b2Vec2& center, const color& col );
			~label();

			void draw() const;
			float get_width() const;
			float get_height() const;

		private:
			std::string text;
			b2Vec2 center;
			rect aabb;
			font *typography;
			std::vector<vertex> vertices;
	};
};

#endif