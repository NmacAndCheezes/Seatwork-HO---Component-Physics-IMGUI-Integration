#include "Cube.h"
#include "Vector3D.h"
#include <iostream>
#include "Rotator.h"
#include "PrimitiveRenderer.h"

void Cube::initialize(TexturePtr tex)
{
	PrimitiveRenderer* pr = new PrimitiveRenderer(CUBE, tex);
	attachComponent(pr);
}

Cube::Cube(TexturePtr tex) : AGameObject("Cube")
{
	initialize(tex);
}

void Cube::update()
{
	AGameObject::update();
}

Cube::~Cube()
{
	
}
