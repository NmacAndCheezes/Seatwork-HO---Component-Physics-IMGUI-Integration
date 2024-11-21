#pragma once

#include "Component.h"
class TestAnimation3 : public Component
{
public:
	TestAnimation3();
	virtual void update() override;
	~TestAnimation3();

private:
	float m_delta_pos;
	float m_delta_scale;
};