#define GLFW_NO_GLU
#include <GL/glfw.h>
#include "texture.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using namespace slge;

texture::texture()
	:	resource(),
		name(0)
{
}

texture::~texture()
{
	glDeleteTextures( 1, &name );
}

bool texture::load( const std::string& fp, int w, int h )
{
	if( fp.empty() ) return false;

	filename = fp;
	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &name );
	glBindTexture( GL_TEXTURE_2D, name );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	if( !glfwLoadTexture2D( filename.c_str(), GLFW_ORIGIN_UL_BIT ) )
	{
		cerr << "Failed to load texture with path: " << filename << endl;
		glDisable( GL_TEXTURE_2D );
		return false;
	}
	glDisable( GL_TEXTURE_2D );
	loaded = true;
	return true;
}
