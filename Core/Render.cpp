#include "Render.h"
#include <Windows.h>
#include <gl/GL.h>
#include "Settings.h"

using namespace std;
using namespace slge;

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& Color)
{
        glColor3f(Color.r, Color.g, Color.b);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < vertexCount; ++i)
        {
                glVertex2f(vertices[i].x * PTM_RATIO, vertices[i].y * PTM_RATIO);
        }
        glEnd();
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& Color)
{
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.5f * Color.r, 0.5f * Color.g, 0.5f * Color.b, 0.5f);
        glBegin(GL_TRIANGLE_FAN);
        for (int32 i = 0; i < vertexCount; ++i)
        {
                glVertex2f(vertices[i].x * PTM_RATIO, vertices[i].y * PTM_RATIO);
        }
        glEnd();
        glDisable(GL_BLEND);

        glColor4f(Color.r, Color.g, Color.b, 1.0f);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < vertexCount; ++i)
        {
                glVertex2f(vertices[i].x * PTM_RATIO, vertices[i].y * PTM_RATIO );
        }
        glEnd();
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& Color)
{
        const float32 kSegments = 16.0f;
        const float32 kIncrement = 2.0f * b2_pi / kSegments;
        float32 theta = 0.0f;
        glColor3f(Color.r, Color.g, Color.b);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < kSegments; ++i)
        {
                b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
                glVertex2f(v.x * PTM_RATIO, v.y * PTM_RATIO);
                theta += kIncrement;
        }
        glEnd();
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& Color)
{
        const float32 kSegments = 16.0f;
        const float32 kIncrement = 2.0f * b2_pi / kSegments;
        float32 theta = 0.0f;
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.5f * Color.r, 0.5f * Color.g, 0.5f * Color.b, 0.5f);
        glBegin(GL_TRIANGLE_FAN);
        for (int32 i = 0; i < kSegments; ++i)
        {
                b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
                glVertex2f(v.x * PTM_RATIO, v.y * PTM_RATIO);
                theta += kIncrement;
        }
        glEnd();
        glDisable(GL_BLEND);

        theta = 0.0f;
        glColor4f(Color.r, Color.g, Color.b, 1.0f);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < kSegments; ++i)
        {
                b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
                glVertex2f(v.x * PTM_RATIO, v.y * PTM_RATIO);
                theta += kIncrement;
        }
        glEnd();

        b2Vec2 p = center + radius * axis;
        glBegin(GL_LINES);
        glVertex2f(center.x * PTM_RATIO, center.y * PTM_RATIO);
        glVertex2f(p.x * PTM_RATIO, p.y * PTM_RATIO);
        glEnd();
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& Color)
{
        glColor3f(Color.r, Color.g, Color.b);
        glBegin(GL_LINES);
        glVertex2f(p1.x * PTM_RATIO, p1.y * PTM_RATIO);
        glVertex2f(p2.x * PTM_RATIO, p2.y * PTM_RATIO);
        glEnd();
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{

}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& Color)
{
        glPointSize(size);
        glBegin(GL_POINTS);
        glColor3f(Color.r, Color.g, Color.b);
        glVertex2f(p.x * PTM_RATIO, p.y * PTM_RATIO);
        glEnd();
        glPointSize(1.0f);
}

void DebugDraw::DrawString(int x, int y, const char *string, ...)
{

}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
        glColor3f(c.r, c.g, c.b);
        glBegin(GL_LINE_LOOP);
        glVertex2f(aabb->lowerBound.x * PTM_RATIO, aabb->lowerBound.y * PTM_RATIO);
        glVertex2f(aabb->upperBound.x * PTM_RATIO, aabb->lowerBound.y * PTM_RATIO);
        glVertex2f(aabb->upperBound.x * PTM_RATIO, aabb->upperBound.y * PTM_RATIO);
        glVertex2f(aabb->lowerBound.x * PTM_RATIO, aabb->upperBound.y * PTM_RATIO);
        glEnd();
}
