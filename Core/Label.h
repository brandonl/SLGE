#ifndef __LABEL_H__
#define __LABEL_H__

#include <string>
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
			const float			getHWidth() const;
			const float			getHHeight() const;
			const glm::vec2&	getCenter() const;

		private:
			const Text2 &textBuilder;
			std::string text;
			Quad bounds;
			VertList vertices;
	};

	inline const float Label::getHWidth() const
	{
		return bounds.hwidth;
	}

	inline const float Label::getHHeight() const
	{
		return bounds.hheight;
	}
	inline const glm::vec2&	Label::getCenter() const
	{
		return bounds.center;
	}
};

#endif
