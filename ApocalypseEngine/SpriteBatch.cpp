#include "SpriteBatch.h"

#include <algorithm>


SpriteBatch::SpriteBatch() : _vaoID(0), _vboID(0)
{
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(SortType sortType /*TEXTURE*/)
{
	_sortType = sortType;
	_renderBatches.clear();

	for (int i = 0; i < _glyphs.size(); i++)
		delete _glyphs[i];

	_glyphs.clear();
}

void SpriteBatch::end()
{
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::addToBatch(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tex, const Color& color)
{
	Glyph* newGlyph = new Glyph;
	newGlyph->texture = tex;
	newGlyph->depth = depth;

	newGlyph->topLeft.color = color;
	newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
	newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	newGlyph->topRight.color = color;
	newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	_glyphs.push_back(newGlyph);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(_vaoID);

	for (int i = 0; i < _renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}

	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	std::vector<Vertex2D> vertices;
	vertices.resize(_glyphs.size() * 6);

	if (_glyphs.empty())
		return;

	int currentVert = 0;
	int offset = 0;

	//Create first render batch
	_renderBatches.emplace_back(0, 6, _glyphs[0]->texture);

	vertices[currentVert++] = _glyphs[0]->topLeft;
	vertices[currentVert++] = _glyphs[0]->bottomLeft;
	vertices[currentVert++] = _glyphs[0]->bottomRight;
	vertices[currentVert++] = _glyphs[0]->bottomRight;
	vertices[currentVert++] = _glyphs[0]->topRight;
	vertices[currentVert++] = _glyphs[0]->topLeft;
	offset += 6;

	//Loop through rest of glyphs
	for (int cg = 1; cg < _glyphs.size(); cg++) {
		if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture)	//Make sure there isn't a render batch already set up for current texture
			_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
		else
			_renderBatches.back().numVertices += 6;

		vertices[currentVert++] = _glyphs[cg]->topLeft;
		vertices[currentVert++] = _glyphs[cg]->bottomLeft;
		vertices[currentVert++] = _glyphs[cg]->bottomRight;
		vertices[currentVert++] = _glyphs[cg]->bottomRight;
		vertices[currentVert++] = _glyphs[cg]->topRight;
		vertices[currentVert++] = _glyphs[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), nullptr, GL_DYNAMIC_DRAW);	//orphan the buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex2D), vertices.data());	//upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray()
{
	if (_vaoID == 0)
		glGenVertexArrays(1, &_vaoID);

	glBindVertexArray(_vaoID);

	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, uv));

	glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs()
{
	switch (_sortType) {
		case SortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), sortBackToFront);
			break;

		case SortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), sortFrontToBack);
			break;

		case SortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), sortTexture);
			break;
	}
}

bool SpriteBatch::sortBackToFront(Glyph* a, Glyph* b)
{
	return (a->depth < b->depth);
}

bool SpriteBatch::sortFrontToBack(Glyph* a, Glyph* b)
{
	return (a->depth > b->depth);
}

bool SpriteBatch::sortTexture(Glyph* a, Glyph* b)
{
	return (a->texture < b->texture);
}

SpriteBatch::~SpriteBatch()
{
}