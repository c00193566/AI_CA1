#pragma once
#include "stdafx.h"
#include "RenderSystem.h"

using namespace sf;

class Scene
{
public:
	virtual ~Scene() {};
	virtual void Update(unsigned int) = 0;
	virtual void Render(RenderSystem * Renderer) = 0;
	virtual void Event(RenderSystem * Renderer) = 0;
	virtual bool Running() = 0;

protected:
	bool IsRunning;

};