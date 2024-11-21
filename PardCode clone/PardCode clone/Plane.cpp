#include "Plane.h"
#include "AGameObjectManager.h"
#include "PrimitiveRenderer.h"

void Plane::initialize(TexturePtr tex)
{
	PrimitiveRenderer* pr = new PrimitiveRenderer(PLANE, tex);
}

Plane::Plane() : Cube(TexturePtr())
{
	setName("Plane");
}

Plane::Plane(TexturePtr tex) : Cube(tex)
{
	initialize(tex);
	setName("Plane");
}

void Plane::update()
{
	AGameObject::update();
}

Plane::~Plane()
{
}
