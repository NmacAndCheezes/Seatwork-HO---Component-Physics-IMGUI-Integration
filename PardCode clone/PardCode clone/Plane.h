#pragma once
#include "Cube.h"

class Plane : public Cube
{
public:
	void initialize(TexturePtr tex);
	Plane();
	Plane(TexturePtr tex);

	virtual void update() override;
	~Plane();
};