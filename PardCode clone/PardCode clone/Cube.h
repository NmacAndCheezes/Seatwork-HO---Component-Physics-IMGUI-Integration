#pragma once
#include "Window.h"
#include "TextureManager/Texture.h"
#include "AGameObject.h"

class Cube : public AGameObject
{
public:
	virtual void initialize(TexturePtr tex);
	Cube(TexturePtr tex);
	virtual void update() override;
	~Cube();
};

