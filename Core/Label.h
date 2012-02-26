#ifndef LABEL_H
#define LABEL_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "Font.h"
#include <string>
#include <glm/glm.hpp>
#include "Color.h"
#include <vector>
#include "Vertex.h"
#include "Rect.h"

namespace slge
{
	class Label
	{
		public:
			explicit Label() {};
			explicit Label( const std::string &text, Font *f, const glm::vec2& center, const Color& col );
			~Label();

			void draw() const;
			float getWidth() const;
			float getHeight() const;
			glm::vec2 center;

		private:
			std::string text;
			Rect aabb;
			Font *typography;
			std::vector<Vertex> vertices;
	};
};

#endif
