#pragma once
#include "Component.h"
class Rotator : public Component
{
public:
	Rotator();
	Rotator(const Vector3D& vector);
	virtual void update() override;
	~Rotator();
private:
	Vector3D rotationSpeed;
};

