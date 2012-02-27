#define GLFW_NO_GLU
#include <GL/glfw.h>
#include "Window.h"
#include <iostream>

using namespace slge;

Window *Window::instance = NULL;

Window::Window()
{
	if( instance != NULL )
		std::cerr << "Only one Window may be active at a time."<< std::endl;

	instance = this;
}

Window::~Window()
{
	glfwCloseWindow();
	glfwTerminate();
}

void Window::init( const std::string& ntitle, int w, int h, int cdepth, int zdepth )
{
	title = ntitle;
	width = w;
	height = h;
	cdepth = cdepth;
	zbdepth = zdepth;
	ratio = ( static_cast<GLfloat>( width ) / height );

	if( !glfwInit() )
		std::cerr <<  "GLFW Error: Failed to initialize GLFW" << std::endl;

	int bitsPerColor = cdepth / 4;

	if( !glfwOpenWindow( 	width, height,
									bitsPerColor, bitsPerColor, bitsPerColor, bitsPerColor,
									zbdepth, 0,
									GLFW_WINDOW ) )
		std::cerr <<  "GLFW Error:  Failed to open GL Context Window"<< std::endl;

	this->center();

	glfwSetWindowTitle( title.c_str() );

	// Disable polling on swap buffers; we will call on our own terms.
	glfwDisable( GLFW_AUTO_POLL_EVENTS );
	glfwEnable( GLFW_KEY_REPEAT );
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );
	glfwSetWindowSizeCallback( windowResize );

	//OpenGL Immediate mode set-up
	//TODO: Remove when OGL3 Core
	if( height == 0 )
		height = 1;

	glViewport( 0, 0, width, height );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, width, height, 0.0f, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable( GL_TEXTURE_2D );
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );

	glDisable( GL_DEPTH_TEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}


void Window::windowResize( int w, int h )
{
	instance->width = w;
	instance->height = h;

	glViewport( 0, 0, instance->width, instance->height );
}

void Window::update()
{
	glfwPollEvents();
}

void Window::clear()
{
	glClear( GL_COLOR_BUFFER_BIT );
}

void Window::swapBuffers()
{
	glfwSwapBuffers();
}

bool Window::isOpen()
{
	return ( glfwGetWindowParam( GLFW_OPENED ) == 0 ? false : true );
}

int Window::getWidth()
{
	return instance->width;
}

int Window::getHeight()
{
	return instance->height;
}

float Window::getAspectRatio()
{
	return instance->ratio;
}

double Window::tick()
{
	return glfwGetTime();
}

void Window::setTitle( const std::string& ntitle )
{
	glfwSetWindowTitle( ntitle.c_str() );
}

void Window::center()
{
	int *displaySize = instance->displaySize();

	glfwGetWindowSize( &instance->width, &instance->height );
	glfwSetWindowPos( ( displaySize[0] - instance->width ) / 2, ( displaySize[1] - instance->height ) / 2 );
}

int *Window::displaySize()
{
	GLFWvidmode desktopResolution;
	glfwGetDesktopMode( &desktopResolution );
	static int displaySize[2] = { desktopResolution.Width, desktopResolution.Height };
	return displaySize;
}