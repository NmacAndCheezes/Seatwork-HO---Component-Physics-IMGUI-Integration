#pragma once
#include "Vector3D.h"
#include "Matrix4x4.h"

class AGameObject;
class Transform
{
public:
	Transform(AGameObject* attachedObj);
	Transform(AGameObject* attachedObj, const Vector3D& initialPosition);
	Transform(AGameObject* attachedObj, const Vector3D& initialPosition, const Vector3D& initialRotation);
	Transform(AGameObject* attachedObj, const Vector3D& initialPosition, const Vector3D& initialRotation, const Vector3D& initialScale);
	~Transform();

	void update();

	void SetPosition(const Vector3D& vector);
	void SetLocalPosition(const Vector3D& vector);

	void SetRotation(const Vector3D& vector);
	void SetLocalRotation(const Vector3D& vector);

	void SetScale(const Vector3D& vector);
	void SetLocalScale(const Vector3D& vector);

	Vector3D position();
	Vector3D localPosition();

	Vector3D rotation();
	Vector3D localRotation();

	Vector3D scale();
	Vector3D localScale();

	Matrix4x4 getTransformMatrix();
	void setPhysicsMatrix(const float matrix[16]); //for rigidbody updates only
	float* getPhysicsLocalMatrix(); //scale is set to 1.0
	void RecalculateChildTransformWithoutParent();
	void RecalculateChildTransformWithParent(const Transform* parent);
private:
	Vector3D m_local_pos;
	Vector3D m_local_rot;
	Vector3D m_local_scale;

	Matrix4x4 m_transform_matrix;

	AGameObject* m_attachedObj = nullptr;
};

