#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

struct Position {
	float x, y;
};

struct Color {
	Color() : r(0), g(0), b(0), a(0) {};
	Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) {};

	GLubyte r, g, b, a;
};

struct UV {
	float u, v;
};

struct Vertex2D
{
	Position position;
	Color color;
	UV uv;

	inline void setPosition(float x, float y) { position.x = x; position.y = y; }
	inline void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) { color.r = r; color.g = g; color.b = b; color.a = a; }
	inline void setUV(float u, float v) { uv.u = u; uv.v = v; }
};