#ifndef FONT_H
#define FONT_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "Resource.h"

namespace slge
{
	class Font : public Resource
	{
		public:

			struct glyphData
			{
			   float x0, y0, s0, t0; // top-left
			   float x1, y1, s1, t1; // bottom-right
			};

			explicit Font();
			~Font();

			bool load(	const std::string &fp,
						float size,
						unsigned int texWidth = 0,
						unsigned int texHeight = 0 );

			void use() const;
			void toss() const;
			glyphData getGlyphData( char c, float *x, float *y ) const;

			float pixelHeight;
			unsigned int textureWidth;
			unsigned int textureHeight;

		private:
			unsigned int texid;
			void* cdata;

	};
};

#endif
