#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <cstdio>
#include <Box2D.h>

namespace slge
{
	class Entity // : public Node
	{
		public:
			explicit Entity( const std::string groupName = "", Scene *parent = nullptr ) 
				:  group(groupName), 
					condemned(false),
					parent(parent)
			{
				printf( "Create entity: %s\n", group.c_str() );
			}

			virtual ~Entity() 
			{ 
				printf( "Destroying entity: %s\n", group.c_str() );
			}

			void load()
			{
				doLoad();
			}

			void update()
			{
				doUpdate();
			}

			void draw() const
			{
				doDraw();
			}

			void setParent( const Scene *p )
			{
				parent = p;
			}

			const Scene* getParent() const
			{
				return parent;
			}

		private:
			virtual void doLoad() = 0;
			virtual void doUpdate() = 0;
			virtual void doDraw() const = 0;

			unsigned id;
			std::string group;
			bool condemned;
			const Scene *parent;

			friend class Scene;
	};
};
#endif
