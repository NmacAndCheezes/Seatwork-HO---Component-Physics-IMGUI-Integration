#pragma once
#include "Point.h"

class InputListener
{
public:
	InputListener()
	{

	}
	~InputListener()
	{

	}

	virtual void onKeyDown(int key) {};
	virtual void onKeyUp(int key) {};
	
	//Mouse
	virtual void onMouseMove(const Point& mouse_pos) {};

	virtual void onLeftMouseDown(const Point& delta_mouse_pos) {};
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) {};

	virtual void onRightMouseDown(const Point& delta_mouse_pos) {};
	virtual void onRightMouseUp(const Point& delta_mouse_pos) {};
};
