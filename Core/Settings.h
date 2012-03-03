#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "Color.h"

#define CENTER_X			( slge::Window::getWidth() >> 1 )
#define CENTER_Y			( slge::Window::getHeight() >> 1 )
#define WINDOW_CENTER	glm::vec2( CENTER_X, CENTER_Y )

#define WINDOW_WIDTH ( Window::getWidth() )
#define WINDOW_HEIGHT ( Window::getHeight() )

namespace slge
{
	const double	FIXED_UPDATE_SPEED = 60.0;
	const float		FIXED_UPDATE_SPEEDF = 60.f;
	const double	DELTA_TIME = 1.0/FIXED_UPDATE_SPEED;
	const float		DELTA_TIMEF = 1.f/FIXED_UPDATE_SPEEDF;
	const float		PTM_RATIO = 32.f;
	const float		SLGE_GRAVITY = 15.f;
	const unsigned		INIT_WINDOW_WIDTH = 480u;
	const unsigned		INIT_WINDOW_HEIGHT = 640u;
	const float		TTF_DEFAULT_PIXEL_HEIGHT = 11.f;
	const int		TTF_FONT_WIDTH = 512;
	const int		TTF_FONT_HEIGHT = 512;

	const float		PI				= 3.14159265358979f;
	const float		RAD2DEG		= 57.29578f;
	const float		DEG2RAD		= 0.01745329f;

	const	Color		CLEAR_COLOR = Color( "3C3C44" );
	static const char* RESOURCE_DIR = "../../Resources/";
};

#endif