#pragma once

#include "Vertex2D.h"

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

enum class SortType {
	NONE, 
	BACK_TO_FRONT, 
	FRONT_TO_BACK, 
	TEXTURE
};

struct Glyph {
	Vertex2D topLeft, bottomLeft, topRight, bottomRight;
	GLuint texture;
	float depth;
};

class RenderBatch {
public:
	RenderBatch(GLuint Offset, GLuint NumVerts, GLuint Texture) : offset(Offset), numVertices(NumVerts), texture(Texture) {}

	GLuint offset, numVertices, texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();
	void begin(SortType sortType = SortType::TEXTURE);
	void end();
	void addToBatch(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tex, const Color& color);
	void renderBatch();

private:
	GLuint _vaoID, _vboID;
	SortType _sortType;

	std::vector<RenderBatch> _renderBatches;
	std::vector<Glyph*> _glyphs;

	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool sortBackToFront(Glyph* a, Glyph* b);
	static bool sortFrontToBack(Glyph* a, Glyph* b);
	static bool sortTexture(Glyph* a, Glyph* b);
};