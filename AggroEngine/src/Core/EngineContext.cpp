#include "EngineContext.hpp"

EngineContext::EngineContext()
	: m_graphics(shared_ptr<OpenGL43Graphics>(new OpenGL43Graphics()))
	, m_fps(60)
	, m_vboCache(shared_ptr<VertexBufferCache>(new VertexBufferCache(m_graphics)))
	, m_textureCache(shared_ptr<TextureCache>(new TextureCache(m_graphics)))
	, m_scene(shared_ptr<Scene>(new Scene()))
{
}

shared_ptr<Graphics> EngineContext::getGraphics()
{
	return m_graphics;
}

shared_ptr<VertexBufferCache> EngineContext::getVboCache()
{
	return m_vboCache;
}

shared_ptr<TextureCache> EngineContext::getTextureCache()
{
	return m_textureCache;
}

shared_ptr<Scene> EngineContext::getScene()
{
	return m_scene;
}

int EngineContext::getFPS()
{
	return m_fps;
}

void EngineContext::setFPS(int fps)
{
	m_fps = fps;
}