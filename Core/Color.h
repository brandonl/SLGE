#ifndef COLOR_H
#define COLOR_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <string>

namespace slge
{
	class Color
	{
		public:
			explicit Color();
			explicit Color( float r, float g, float b, float a );
			explicit Color( const std::string &hexValue );

			float r, g, b, a;

			static Color black;
			static Color orange;
			static Color grey;
			static Color purple;
			static Color yellow;
			static Color xred;
			static Color red;
			static Color cyan;
			static Color green;
			static Color blue;

	};
};
#endif
