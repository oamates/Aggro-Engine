#pragma once

#include "Component.hpp"
#include "GraphicsContext.hpp"
#include "Matrix.hpp"

/**
 * Abstract Component that defines rendering behavior
 *
 * author: wcrane
 * since: 2014-05-18
**/
class RenderComponent : public Component
{
public:
	RenderComponent();

	virtual void render(shared_ptr<GraphicsContext> context, glm::mat4 m4Transform, int objId) = 0;
};