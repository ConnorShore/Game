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

class Glyph {
public:
	Glyph() {};
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, GLuint Texture, const Color& color);
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, GLuint Texture, const Color& color, float angle);

	Vertex2D topLeft, bottomLeft, topRight, bottomRight;
	GLuint texture;
	float depth;

private:
	glm::vec2 rotatePoint(glm::vec2 point, float angle);
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
	void addToBatch(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tex, const Color& color, float angle);
	void addToBatch(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tex, const Color& color, const glm::vec2& direction);
	void renderBatch();

private:
	GLuint _vaoID, _vboID;
	SortType _sortType;

	std::vector<RenderBatch> _renderBatches;
	std::vector<Glyph> _glyphs;
	std::vector<Glyph*>  _glyphPointers;

	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool sortBackToFront(Glyph* a, Glyph* b);
	static bool sortFrontToBack(Glyph* a, Glyph* b);
	static bool sortTexture(Glyph* a, Glyph* b);
};