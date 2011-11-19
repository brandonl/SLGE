#ifndef COLOR_H
#define COLOR_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <string>

namespace slge
{
	class color
	{
		public:
			explicit color();
			explicit color( float r, float g, float b, float a );
			explicit color( const std::string &hex_value );

			float r, g, b, a;

			static color black;
			static color orange;
			static color grey;
			static color purple;
			static color yellow;
			static color xred;
			static color red;
			static color cyan;
			static color green;
			static color blue;

	};
};
#endif