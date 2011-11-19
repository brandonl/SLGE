#include "color.h"
#include <sstream>

using namespace slge;

color color::black	= color( 0.0f, 0.0f, 0.0f, 1.0f );
color color::grey	= color( 0.5f, 0.5f, 0.5f, 1.0f );
color color::yellow = color( 0.0f, 1.0f, 1.0f, 1.0f );
color color::orange = color( 1.0f, 0.5f, 0.0f, 1.0f );
color color::purple = color( 0.5f, 0.0f, 1.0f, 1.0f );
color color::xred	= color( 1.0f, 0.4f, 0.32f, 1.0f );
color color::cyan	= color( 0.5f, 0.5f, 1.0f, 1.0f );
color color::red	= color( 1.0f, 0.0f, 0.0f, 1.0f );
color color::blue	= color( 0.0f, 0.0f, 1.0f, 1.0f );
color color::green	= color( 0.0f, 1.0f, 0.0f, 1.0f );

color::color()
	:	r(1.0f),
		g(1.0f),
		b(1.0f),
		a(1.0f)
{}

color::color( float r, float g, float b, float a )
	:	r(r),
		g(g),
		b(b),
		a(a)
{}

color::color( const std::string &hex_value )
{
	std::istringstream is( hex_value );

	unsigned int hexcolor;
	is >> std::hex >> hexcolor;

	r = (float)( ( hexcolor >> 16 ) & 0xFF );
	g = (float)( ( hexcolor >> 8 ) & 0xFF );
	b = (float)( hexcolor & 0xFF );
	r /= 255.0f;
	g /= 255.0f;
	b /= 255.0f;
	a = 1.0f;
}

