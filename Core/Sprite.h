#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <string>
#include <vector>
#include "Vertex.h"
#include "Texture2D.h"
#include <glm/glm.hpp>

namespace slge
{
	class Sprite
	{
		public:
			// Using string version will cause a new texture to be loaded in the GPU even if 
			// the image was already cached. Simply here for a convienence.
			Sprite( const Texture2 &textureSheet, int width, int height, const Color& = Color() );

			void draw() const
			{
				doDraw();
			}

			void update()
			{
				doUpdate();
			}

			const int getHWidth() const
			{
				return hwidth;
			}

			const int getHHeight() const
			{
				return hheight;
			}

			const bool isVisible() const
			{
				return visible;
			}

			void toggleVisibility()
			{
				visible = visible ? false : true;
			}

		private:
			virtual void doDraw() const;
			virtual void doUpdate() = 0;

		protected:
			const Texture2 &textureSheet;
			VertList quad;
			int hwidth;
			int hheight;
			bool visible;
			glm::vec2 texOffset;
			glm::vec2 texScale;
	};

	class StaticSprite : public Sprite
	{
		public:
			StaticSprite( const Texture2 &textureSheet, int width = -1, int height = -1, const Color& col = Color() )
				: Sprite( textureSheet, width, height, col ){}

		private:
			void doUpdate() {}
	};

	class AnimatedSprite : public Sprite
	{
		struct Animation
		{
			Animation( const std::string &name, unsigned start, unsigned end, unsigned level, float speed );

			std::string name;
			unsigned frame;
			unsigned start;
			unsigned end;
			unsigned level;
			float speed;
			float lastUpdate;
		};

		public:
			AnimatedSprite( const Texture2 &textureSheet, int width = -1, int height = -1, const Color& col = Color() )
				:	Sprite( textureSheet, width, height, col ),
					currentAnim(nullptr)
			{}

			void add( const std::string &anim, unsigned int start, unsigned int end, unsigned int level, float speed );
			void play( const std::string &anim );
			void stop( const std::string &anim );

		private:
			void doUpdate();

		private:
			Animation *currentAnim;
			std::vector<Animation> anims;
			Animation *get( const std::string &anim );
	};

};

#endif
