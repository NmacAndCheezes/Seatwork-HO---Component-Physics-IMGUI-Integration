#pragma once
//#include "Component.h" for implementing game camera
#include "Matrix4x4.h"
#include "AppWindow.h"

enum ProjectionType { perspective = 0, orthographic = 1, isometric = 2 };
class Camera
{
public:
	Camera(AppWindow* window);
	Matrix4x4 getViewMatrix();
	Matrix4x4 getProjectionMatrix();
	void setViewType(int new_proj_type);

	Matrix4x4 getPositionMatrix();
	Matrix4x4 getRotationMatrix();
	virtual void updateCamera() = 0;
	~Camera();

	void SetPosition(const Vector3D& newPos);
	void SetRotation(const Vector3D& newRot);

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	Vector3D position();
	Vector3D rotation();

	bool getIsEnabled() { return isEnabled; }
protected:
	AppWindow* m_window;

	Vector3D m_position;
	Vector3D m_rotation;
	Matrix4x4 m_viewMatrix;
	Matrix4x4 m_projectionMatrix;

	ProjectionType ProjectionType = perspective;
	bool isEnabled = true;
};

