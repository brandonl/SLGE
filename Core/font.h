#ifndef FONT_H
#define FONT_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "resource.h"

namespace slge
{
	class font : public resource
	{
		public:

			struct glyph_data
			{
			   float x0, y0, s0, t0; // top-left
			   float x1, y1, s1, t1; // bottom-right
			};

			explicit font();
			~font();

			bool load(	const std::string &fp, 
						float size, 
						unsigned int tex_width = 0, 
						unsigned int tex_height = 0 );

			void use() const;
			void toss() const;
			glyph_data get_glyph_data( char c, float *x, float *y ) const;

			float pixel_height;
			unsigned int texture_width;
			unsigned int texture_height;

		private:
			unsigned int texid;
			void* cdata;

	};
};

#endif