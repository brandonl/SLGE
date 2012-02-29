#ifndef __DEFINES_H__
#define __DEFINES_H__

namespace slge
{
	static const double	FIXED_UPDATE_SPEED = 60.0;
	static const double	DELTA_TIME = 1.0/FIXED_UPDATE_SPEED;
	static const float	PTM_RATIO = 32.f;

	static const float	TTF_DEFAULT_PIXEL_HEIGHT = 16.f;
	static const int		TTF_FONT_WIDTH = 512;
	static const int		TTF_FONT_HEIGHT = 512;

	static const char*	RESOURCE_DIR = "../../Resources/";
};

#endif