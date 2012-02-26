#ifndef SPRITE_H
#define SPRITE_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include "ResourceModule.h"
#include <vector>
#include <string>
#include <list>
#include "Vertex.h"
#include <glm/glm.hpp>

namespace slge
{
	class Sprite
	{
		class Animation
		{
			public:
				Animation() {}
				Animation( const std::string &name, unsigned int start, unsigned int end, unsigned int level, float speed );

				std::string name;
				unsigned int frame;
				unsigned int start;
				unsigned int end;
				unsigned int level;
				float speed;
				float lastUpdate;
		};

		public:
			explicit Sprite() {};
			explicit Sprite( const std::string&, float, float, int, int, const Color& = Color() );
			~Sprite();
			void draw();
			void update();

			void add( const std::string &anim, unsigned int start, unsigned int end, unsigned int level, float speed );
			void play( const std::string &anim );
			void stop( const std::string &anim );

			float getHwidth() const;
			float getHheight() const;
			bool visible;

		private:
			Texture* sheet;
			glm::vec2 texOffset, texScale;
			float width, height;
			int tw, th;
			std::vector<Vertex> vertices;

			Animation *get( const std::string &anim );
			std::list<Animation> anims;
			Animation *currentAnim;

	};

};

#endif
