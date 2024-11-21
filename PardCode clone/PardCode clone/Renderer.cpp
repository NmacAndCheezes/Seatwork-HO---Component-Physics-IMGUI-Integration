#include "Renderer.h"
#include "AGameObjectManager.h"

Renderer::Renderer() : Component(Component::renderer)
{
	
}

Renderer::~Renderer()
{
	attachedObject = nullptr;
}
