#pragma once
#include "Component.h"

class WarpCubeToPlane : public Component
{
public:
	WarpCubeToPlane() : Component(Component::script) {} 
	virtual void update() override;
	~WarpCubeToPlane() {}

private:
	float m_delta_scale = 0.0f;
};