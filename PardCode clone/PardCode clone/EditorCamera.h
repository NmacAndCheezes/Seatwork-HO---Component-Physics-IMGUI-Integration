#pragma once
#include "Camera.h"
#include "InputListener.h"

class EditorCamera : public Camera, public InputListener
{
public:
	EditorCamera(AppWindow* window);
	virtual void updateCamera() override;
	void move();
	~EditorCamera();

#if 1
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	//Mouse
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onRightMouseDown(const Point& delta_mouse_pos) override;
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override;
#endif
	void SetInitialPosition(const Vector3D& newPos);
	void SetInitialRotation(const Vector3D& newRot);
	void SetInitialPosition(float x, float y, float z);
	void SetInitialRotation(float x, float y, float z);
private:
	Vector3D initialPosition = Vector3D();
	Vector3D initialRotation = Vector3D();
	POINT current_mouse_pos = {};
	bool is_HoldingP = false;
	int viewType = 0;
	float m_forward;
	float m_right;
};

