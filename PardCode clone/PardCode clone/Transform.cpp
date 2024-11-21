#include "Transform.h"
#include "AGameObject.h"
#include "Math.h"

Transform::Transform(AGameObject* attachedObj)
	: m_attachedObj(attachedObj), m_local_pos(Vector3D()), m_local_rot(Vector3D()), m_local_scale(Vector3D(1, 1, 1)) 
{
	update();
}

Transform::Transform(AGameObject* attachedObj, const Vector3D& position)
	: m_attachedObj(attachedObj), m_local_pos(position), m_local_rot(Vector3D()), m_local_scale(Vector3D(1, 1, 1)) 
{
	update();
}

Transform::Transform(AGameObject* attachedObj, const Vector3D& position, const Vector3D& rotation)
	: m_attachedObj(attachedObj), m_local_pos(position), m_local_rot(rotation), m_local_scale(Vector3D(1, 1, 1)) 
{ 
	update();
}

Transform::Transform(AGameObject* attachedObj, const Vector3D& position, const Vector3D& rotation, const Vector3D& scale)
	: m_attachedObj(attachedObj), m_local_pos(position), m_local_rot(rotation), m_local_scale(scale) 
{ 
	update();
}

void Transform::update()
{
	m_transform_matrix.setIdentity();
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setTranslation(this->localPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->localScale());

	Vector3D rotation = this->localRotation();
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.Z());
	//zMatrix.printMatrix();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.X());
	//xMatrix.printMatrix();
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.Y());
	//yMatrix.printMatrix();

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));
	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	m_transform_matrix = allMatrix;

	//std::cout << "Position: " << position().X() << ", " << position().Y() << ", " << position().Z() << ", " << std::endl;
	//std::cout << "Rotation: " << m_local_rot.X() << ", " << m_local_rot.Y() << ", " << m_local_rot.Z() << std::endl;
	//std::cout << "Scale: " << scale().X() << ", " << scale().Y() << ", " << scale().Z() << ", " << std::endl;
}

void Transform::SetPosition(const Vector3D& newPos)
{
	m_local_pos = Vector3D(
		newPos.X() - position().X(),
		newPos.Y() - position().Y(),
		newPos.Z() - position().Z()
	);
	update();
}

void Transform::SetLocalPosition(const Vector3D& vector)
{
	m_local_pos = vector;
	update();
}

void Transform::SetRotation(const Vector3D& newRot)
{
	m_local_rot = Vector3D(
		Math::toRadians(newRot.X() - rotation().X()),
		Math::toRadians(newRot.Y() - rotation().Y()),
		Math::toRadians(newRot.Z() - rotation().Z())
	);
	update();
}

void Transform::SetLocalRotation(const Vector3D& vector)
{
	m_local_rot = vector;
	update();
}

void Transform::SetScale(const Vector3D& newScale)
{
	m_local_scale = Vector3D(
		newScale.X() - scale().X(),
		newScale.Y() - scale().Y(),
		newScale.Z() - scale().Z()
	);
	update();
}

void Transform::SetLocalScale(const Vector3D& vector)
{
	m_local_scale = vector;
	update();
}


Vector3D Transform::position()
{
	Vector3D pos = m_attachedObj->getParent() != nullptr ? 
		m_attachedObj->getParent()->getTransform()->localPosition() + m_local_pos 
		: m_local_pos;
	return pos;
}

Vector3D Transform::localPosition()
{
	return m_local_pos;
}

Vector3D Transform::rotation()
{
	Vector3D rot = m_attachedObj->getParent() != nullptr 
		? m_attachedObj->getParent()->getTransform()->localRotation() + m_local_rot 
		: m_local_rot;
	return Vector3D
	(
		Math::toRadians(rot.X()), Math::toRadians(rot.Y()), Math::toRadians(rot.Z())
	);
}

Vector3D Transform::localRotation()
{
	return m_local_rot;
}

Vector3D Transform::scale()
{
	Vector3D scale = m_attachedObj->getParent() != nullptr ? 
		m_attachedObj->getParent()->getTransform()->localScale() + m_local_scale
		: m_local_scale;
	return scale;
}

Vector3D Transform::localScale()
{
	return m_local_scale;
}

Matrix4x4 Transform::getTransformMatrix()
{
	return m_transform_matrix;
}

void Transform::RecalculateChildTransformWithoutParent()
{
	m_local_pos = position();
	m_local_scale = scale();
	m_local_rot = rotation();

	// no need to update children since the local and global values are still the same 
}

void Transform::RecalculateChildTransformWithParent(const Transform* parent)
{
}

void Transform::setPhysicsMatrix(const float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->localScale());
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->localPosition());
	this->m_transform_matrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
	//m_local_pos = m_transform_matrix.getTranslation();
	//m_local_rot = m_transform_matrix.getRotationDegrees();
	//m_local_scale = m_transform_matrix.getScale();
}

float* Transform::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->localPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(Vector3D::ones()); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->localRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.X());
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.Y());
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.Z());

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	return allMatrix.getMatrix();
}

Transform::~Transform()
{

}
