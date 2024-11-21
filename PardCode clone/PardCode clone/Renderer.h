#pragma once
#include "Component.h"
#include "AppWindow.h"
#include "Vector2D.h"

class Renderer : public Component
{
public:
	Renderer();
	virtual void update() {}
	//virtual void draw(AppWindow* target) = 0;
	~Renderer();
protected:
	struct vertex
	{
		Vector3D position;
		Vector2D texCoord;
	};


	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;
		unsigned int m_time;
	};
};

