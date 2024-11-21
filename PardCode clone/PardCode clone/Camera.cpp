#include "Camera.h"

Camera::Camera(AppWindow* window) : m_window(window)
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}

Matrix4x4 Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}

void Camera::setViewType(int new_proj_type)
{
	if (new_proj_type >= 3)
	{
		new_proj_type %= 3;
	}

	std::string s_proj;

	switch (new_proj_type)
	{
	case 0:
		ProjectionType = perspective;
		s_proj = "perspective";
		break;
	case 1:
		ProjectionType = orthographic;
		s_proj = "orthographic";
		break;
	case 2:
		ProjectionType = isometric;
		s_proj = "isometric";
		break;
	}

	std::cout << "Projection type: " << s_proj << std::endl;
	updateCamera();
}

Matrix4x4 Camera::getPositionMatrix()
{
	Matrix4x4 positionMatrix; positionMatrix.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	temp.setTranslation(m_position);
	positionMatrix = positionMatrix.multiplyTo(temp);

	return positionMatrix;
}

Matrix4x4 Camera::getRotationMatrix()
{
	Matrix4x4 rotationMatrix; rotationMatrix.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	switch (ProjectionType)
	{
	case orthographic:
		temp.setRotationX(0);
		rotationMatrix = rotationMatrix.multiplyTo(temp);

		temp.setRotationY(0);
		rotationMatrix = rotationMatrix.multiplyTo(temp);

		temp.setRotationZ(m_rotation.Z());
		rotationMatrix = rotationMatrix.multiplyTo(temp);
		break;

	default:
		temp.setRotationX(m_rotation.X());
		rotationMatrix = rotationMatrix.multiplyTo(temp);

		temp.setRotationY(m_rotation.Y());
		rotationMatrix = rotationMatrix.multiplyTo(temp);

		temp.setRotationZ(m_rotation.Z());
		rotationMatrix = rotationMatrix.multiplyTo(temp);
	}

	return rotationMatrix;
}

void Camera::updateCamera()
{
	if (!isEnabled) return;

	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	worldCam = getRotationMatrix();
	
	worldCam = worldCam.multiplyTo(getPositionMatrix());
	
	if (ProjectionType == perspective)
	{
		worldCam.inverse();
	}
	
	this->m_viewMatrix = worldCam;

#pragma region Setting Projection Based on projection type;
	switch (ProjectionType)
	{
		case perspective:
			m_projectionMatrix.setPerspectiveFovLH(1, this->m_window->AspectRatio(), 0.1f, 1000.0f);
			break;
		default:
			m_projectionMatrix.setOrthoLH
			(
				(m_window->Width()) / 300.0f,
				(m_window->Height()) / 300.0f,
				-100.0f,
				100.0f
			);
			break;
	}
#pragma endregion
	//this->m_viewMatrix.printMatrix();
}

Camera::~Camera()
{
}

void Camera::SetPosition(const Vector3D& newPos)
{
	m_position = newPos;
	this->updateCamera();
	m_position.printVector("Position");
}

void Camera::SetRotation(const Vector3D& newRot)
{
	m_rotation = newRot;
	this->updateCamera();
	m_rotation.printVector("Rotation");
}

void Camera::SetPosition(float x, float y, float z)
{
	m_position.SetVector(x, y, z);
	this->updateCamera();
	m_position.printVector("Position");
}

void Camera::SetRotation(float x, float y, float z)
{
	m_rotation.SetVector(x, y, z);
	this->updateCamera();
	m_rotation.printVector("Rotation");
}


Vector3D Camera::position()
{
	return m_position;
}

Vector3D Camera::rotation()
{
	return m_rotation;
}
