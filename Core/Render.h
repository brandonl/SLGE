#ifndef RENDER_H
#define RENDER_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

//---------------------------------------------------------------
// Debug Draw Callback functions from Box2D Test Bench
////////////////////////////////////////////////////////////////

#include <Box2D.h>

static const float PTM_RATIO = 32.0f;

class DebugDraw : public b2Draw
{
	public:
		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& Color);

		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& Color);

		void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& Color);

		void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& Color);

		void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& Color);

		void DrawTransform(const b2Transform& xf);

		void DrawPoint(const b2Vec2& p, float32 size, const b2Color& Color);

		void DrawString(int x, int y, const char* string, ...);

		void DrawAABB(b2AABB* aabb, const b2Color& Color);
};

#endif
