#ifndef SPRITE_H
#define SPRITE_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "resourcemodule.h"
#include <vector>
#include <string>
#include <list>
#include "vertex.h"
#include <Box2D.h>

typedef b2Vec2 vec2;

namespace slge
{
	class sprite
	{
		class animation
		{
			public:
				animation() {}
				animation( const std::string &name, unsigned int start, unsigned int end, unsigned int level, float speed );

				std::string name;
				unsigned int frame;
				unsigned int start;
				unsigned int end;
				unsigned int level;
				float speed;
				float last_update;
		};

		public:
			explicit sprite() {};
			explicit sprite( const std::string&, float, float, int, int, const color& = color() );
			~sprite();
			void draw();
			void update();

			void add( const std::string &anim, unsigned int start, unsigned int end, unsigned int level, float speed );
			void play( const std::string &anim );
			void stop( const std::string &anim );

			float get_hwidth() const;
			float get_hheight() const;
			bool visible;

		private:
			texture* sheet;
			vec2 tex_offset, tex_scale;
			float width, height;
			int tw, th;
			std::vector<vertex> vertices;

			animation *get( const std::string &anim );
			std::list<animation> anims;
			animation *current_anim;

	};

};

#endif
