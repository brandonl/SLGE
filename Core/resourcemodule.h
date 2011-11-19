#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <map>
#include "font.h"
#include "texture.h"
#include "utils.h"

namespace slge
{
	class resources : public uncopyable
	{
		public:
			explicit resources();
			~resources();
			void init();

			static void		set_working_dir( const std::string& dir = "Resources/" );
			static texture* grab_texture( const std::string& filename );
			static font*	grab_font(	const std::string &filename, float size = 12.0f, int tex_width = 0, int tex_height = 0 );
			static void		remove_all();
			static void		remove( const std::string& filename );

		private:
			bool add( resource *res );
			resource* request_from_filename( const std::string &filename );

			std::map< std::string, resource* > resource_map;
			std::string working_directory;
			static resources* instance;
	};
};


#endif