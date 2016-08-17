#include "RenderData.hpp"

RenderData::RenderData(shared_ptr<VertexBufferHandle> pVertexBufferHandle, shared_ptr<TextureHandle> pTextureHandle)
	: m_pVertexBufferHandle(pVertexBufferHandle)
	, m_pTextureHandle(pTextureHandle)
	, m_m4ModelMatrix(1.0)
	, m_drawMode(DrawMode::LINE_LOOP)
{
}

RenderData::RenderData(shared_ptr<VertexBufferHandle> pVertexBufferHandle, 
					shared_ptr<TextureHandle> pTextureHandle,
					DrawMode drawMode)
	: m_pVertexBufferHandle(pVertexBufferHandle)
	, m_pTextureHandle(pTextureHandle)
	, m_m4ModelMatrix(1.0)
	, m_drawMode(drawMode)
{
}

RenderData &RenderData::setModelMatrix(glm::mat4 &m4ModelMatrix)
{
	m_m4ModelMatrix = m4ModelMatrix;
	return *this;
}

shared_ptr<VertexBufferHandle> RenderData::getVertexBufferHandle()
{
	return m_pVertexBufferHandle;
}

shared_ptr<TextureHandle> RenderData::getTextureHandle()
{
	return m_pTextureHandle;
}

glm::mat4 &RenderData::getModelMatrix()
{
	return m_m4ModelMatrix;
}

DrawMode RenderData::getDrawMode()
{
	return m_drawMode;
}