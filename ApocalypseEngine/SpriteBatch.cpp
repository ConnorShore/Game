#include "SpriteBatch.h"

#include <algorithm>

Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, GLuint Texture, const Color& color) :
	depth(Depth),
	texture(Texture) {

	topLeft.color = color;
	topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	bottomLeft.color = color;
	bottomLeft.setPosition(destRect.x, destRect.y);
	bottomLeft.setUV(uvRect.x, uvRect.y);

	bottomRight.color = color;
	bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	topRight.color = color;
	topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, GLuint Texture, const Color& color, float angle) :
	depth(Depth),
	texture(Texture) {

	//Center points at origin
	glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

	glm::vec2 tl(-halfDims.x, halfDims.y);
	glm::vec2 tr(halfDims.x, halfDims.y);
	glm::vec2 bl(-halfDims.x, -halfDims.y);
	glm::vec2 br(halfDims.x, -halfDims.y);

	//Rotate points
	tl = rotatePoint(tl, angle) + halfDims;
	tr = rotatePoint(tr, angle) + halfDims;
	bl = rotatePoint(bl, angle) + halfDims;
	br = rotatePoint(br, angle) + halfDims;

	topLeft.color = color;
	topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
	topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	bottomLeft.color = color;
	bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
	bottomLeft.setUV(uvRect.x, uvRect.y);

	bottomRight.color = color;
	bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
	bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	topRight.color = color;
	topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
	topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	

}

glm::vec2 Glyph::rotatePoint(glm::vec2 point, float angle)
{
	glm::vec2 newv;
	newv.x = point.x * cos(angle) - point.y * sin(angle);
	newv.y = point.x * sin(angle) + point.y * cos(angle);
	return newv;
}

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

	_glyphs.clear();
}

void SpriteBatch::end()
{
	_glyphPointers.resize(_glyphs.size());
	for (size_t i = 0; i < _glyphs.size(); i++) {
		_glyphPointers[i] = &_glyphs[i];
	}

	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::addToBatch(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tex, const Color& color)
{
	_glyphs.emplace_back(destRect, uvRect, depth, tex, color);
}

void SpriteBatch::addToBatch(const glm::vec4 & destRect, const glm::vec4 & uvRect, float depth, GLuint tex, const Color & color, float angle)
{
	_glyphs.emplace_back(destRect, uvRect, depth, tex, color, angle);
}

void SpriteBatch::addToBatch(const glm::vec4 & destRect, const glm::vec4 & uvRect, float depth, GLuint tex, const Color & color, const glm::vec2 & direction)
{
	const glm::vec2 right(1.0f, 0.0f);
	float angle = acos(glm::dot(right, direction));
	if (direction.y < 0.0f) angle = -angle;

	_glyphs.emplace_back(destRect, uvRect, depth, tex, color);
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
	vertices.resize(_glyphPointers.size() * 6);

	if (_glyphPointers.empty())
		return;

	int currentVert = 0;
	int offset = 0;

	//Create first render batch
	_renderBatches.emplace_back(0, 6, _glyphPointers[0]->texture);

	vertices[currentVert++] = _glyphPointers[0]->topLeft;
	vertices[currentVert++] = _glyphPointers[0]->bottomLeft;
	vertices[currentVert++] = _glyphPointers[0]->bottomRight;
	vertices[currentVert++] = _glyphPointers[0]->bottomRight;
	vertices[currentVert++] = _glyphPointers[0]->topRight;
	vertices[currentVert++] = _glyphPointers[0]->topLeft;
	offset += 6;

	//Loop through rest of glyphs
	for (int cg = 1; cg < _glyphPointers.size(); cg++) {
		if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture)	//Make sure there isn't a render batch already set up for current texture
			_renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
		else
			_renderBatches.back().numVertices += 6;

		vertices[currentVert++] = _glyphPointers[cg]->topLeft;
		vertices[currentVert++] = _glyphPointers[cg]->bottomLeft;
		vertices[currentVert++] = _glyphPointers[cg]->bottomRight;
		vertices[currentVert++] = _glyphPointers[cg]->bottomRight;
		vertices[currentVert++] = _glyphPointers[cg]->topRight;
		vertices[currentVert++] = _glyphPointers[cg]->topLeft;
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
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), sortBackToFront);
			break;

		case SortType::FRONT_TO_BACK:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), sortFrontToBack);
			break;

		case SortType::TEXTURE:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), sortTexture);
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