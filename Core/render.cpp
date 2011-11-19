#include "render.h"
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <Windows.h>
#include <gl/GL.h>

using namespace std;

void debug_draw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < vertexCount; ++i)
        {
                glVertex2f(vertices[i].x * PTM_RATIO, vertices[i].y * PTM_RATIO);
        }
        glEnd();
}

void debug_draw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
        glBegin(GL_TRIANGLE_FAN);
        for (int32 i = 0; i < vertexCount; ++i)
        {
                glVertex2f(vertices[i].x * PTM_RATIO, vertices[i].y * PTM_RATIO);
        }
        glEnd();
        glDisable(GL_BLEND);

        glColor4f(color.r, color.g, color.b, 1.0f);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < vertexCount; ++i)
        {
                glVertex2f(vertices[i].x * PTM_RATIO, vertices[i].y * PTM_RATIO );
        }
        glEnd();
}

void debug_draw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
        const float32 k_segments = 16.0f;
        const float32 k_increment = 2.0f * b2_pi / k_segments;
        float32 theta = 0.0f;
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < k_segments; ++i)
        {
                b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
                glVertex2f(v.x * PTM_RATIO, v.y * PTM_RATIO);
                theta += k_increment;
        }
        glEnd();
}

void debug_draw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
        const float32 k_segments = 16.0f;
        const float32 k_increment = 2.0f * b2_pi / k_segments;
        float32 theta = 0.0f;
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
        glBegin(GL_TRIANGLE_FAN);
        for (int32 i = 0; i < k_segments; ++i)
        {
                b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
                glVertex2f(v.x * PTM_RATIO, v.y * PTM_RATIO);
                theta += k_increment;
        }
        glEnd();
        glDisable(GL_BLEND);

        theta = 0.0f;
        glColor4f(color.r, color.g, color.b, 1.0f);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < k_segments; ++i)
        {
                b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
                glVertex2f(v.x * PTM_RATIO, v.y * PTM_RATIO);
                theta += k_increment;
        }
        glEnd();

        b2Vec2 p = center + radius * axis;
        glBegin(GL_LINES);
        glVertex2f(center.x * PTM_RATIO, center.y * PTM_RATIO);
        glVertex2f(p.x * PTM_RATIO, p.y * PTM_RATIO);
        glEnd();
}

void debug_draw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_LINES);
        glVertex2f(p1.x * PTM_RATIO, p1.y * PTM_RATIO);
        glVertex2f(p2.x * PTM_RATIO, p2.y * PTM_RATIO);
        glEnd();
}

void debug_draw::DrawTransform(const b2Transform& xf)
{

}

void debug_draw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
        glPointSize(size);
        glBegin(GL_POINTS);
        glColor3f(color.r, color.g, color.b);
        glVertex2f(p.x * PTM_RATIO, p.y * PTM_RATIO);
        glEnd();
        glPointSize(1.0f);
}

void debug_draw::DrawString(int x, int y, const char *string, ...)
{

}

void debug_draw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
        glColor3f(c.r, c.g, c.b);
        glBegin(GL_LINE_LOOP);
        glVertex2f(aabb->lowerBound.x * PTM_RATIO, aabb->lowerBound.y * PTM_RATIO);
        glVertex2f(aabb->upperBound.x * PTM_RATIO, aabb->lowerBound.y * PTM_RATIO);
        glVertex2f(aabb->upperBound.x * PTM_RATIO, aabb->upperBound.y * PTM_RATIO);
        glVertex2f(aabb->lowerBound.x * PTM_RATIO, aabb->upperBound.y * PTM_RATIO);
        glEnd();
}
