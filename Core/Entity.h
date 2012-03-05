#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <Box2D.h>

namespace slge
{
	class Scene;
	class Entity // : public Node
	{
		public:
			explicit Entity( const std::string &groupName = "", Scene *parent = nullptr );
			virtual ~Entity(){}

			void load();
			void update();
			void draw() const;
			void setParent( const Scene *p );
			const Scene* getParent() const;

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
