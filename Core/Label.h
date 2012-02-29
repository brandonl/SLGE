#ifndef __LABEL_H__
#define __LABEL_H__

#include <string>
#include <vector>
#include "Quad.h"
#include "Color.h"
#include "Vertex.h"

namespace slge
{
	class Text2;

	// Static label
	class Label
	{
		public:
			explicit Label( const Text2 &textBuilder, const std::string &text, const glm::vec2& center, const Color& col = Color(), float size = 0.f );
			~Label();

			void draw() const;
			const float			getWidth() const;
			const float			getHeight() const;
			const glm::vec2&	getCenter() const;

		private:
			const Text2 &textBuilder;
			std::string text;
			Quad bounds;
			std::vector<Vertex> vertices;
	};

	inline const float Label::getWidth() const
	{
		return bounds.width;
	}

	inline const float Label::getHeight() const
	{
		return bounds.height;
	}
	inline const glm::vec2&	Label::getCenter() const
	{
		return bounds.center;
	}
};

#endif
