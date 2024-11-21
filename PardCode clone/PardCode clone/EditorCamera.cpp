#include <string>
#include "EditorCamera.h"
#include "InputSystem.h"
#include "EngineTime.h"

EditorCamera::EditorCamera(AppWindow* window) : Camera(window)
{
	initialPosition = m_position;
	initialRotation = m_rotation;
}

void EditorCamera::updateCamera()
{
	Camera::updateCamera();
}

void EditorCamera::move()
{
	if (!isEnabled) return;

	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	worldCam = getRotationMatrix();
	Vector3D new_pos;
	switch (ProjectionType)
	{
	case orthographic:
		new_pos = m_position + Vector3D::up() * (m_forward * 0.1f);
		new_pos = new_pos + Vector3D::right() * (m_right * 0.1f);
		break;
	default:
		new_pos = m_position + (worldCam.getZDirection() * (m_forward * 0.1f));
		new_pos = new_pos + (worldCam.getXDirection() * (m_right * 0.1f));
		break;
	}

	worldCam.setTranslation(new_pos);
	

	m_position = worldCam.getTranslation();
	
	updateCamera();

	m_position.printVector("Position");
}

void EditorCamera::onKeyDown(int key)
{
	float x = m_position.X();
	float y = m_position.Y();
	float z = m_position.Z();
	float moveSpeed = 10.0f;

	if (key == 'W')
	{
		//m_rot_x += 3.14f*m_delta_time;
		m_forward = 1.0f;
		move();
	}
	else if (key == 'S')
	{
		//m_rot_x -= 3.14f*m_delta_time;
		m_forward = -1.0f;
		move();
	}
	else if (key == 'A')
	{
		//m_rot_y += 3.14f*m_delta_time;
		m_right = -1.0f;
		move();
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f*m_delta_time;
		m_right = 1.0f;
		move();
	}
	else if (key == VK_SPACE)
	{
		this->SetPosition(initialPosition);
		this->SetRotation(initialPosition);
	}
	else if (key == 'Q') {
		if (InputSystem::get()->getRightMouseDown())
		{
			y += EngineTime::getDeltaTime() * moveSpeed;
			this->SetPosition(x, y, z);
		}
		else
		{
			float x = m_rotation.X();
			float y = m_rotation.Y();
			float z = m_rotation.Z();

			z -= EngineTime::getDeltaTime() * moveSpeed * 0.1f;
			this->SetRotation(x, y, z);
		}
	}
	else if (key == 'E') {
		if (InputSystem::get()->getRightMouseDown())
		{
			y -= EngineTime::getDeltaTime() * moveSpeed;
			this->SetPosition(x, y, z);
		}
		else
		{
			float x = m_rotation.X();
			float y = m_rotation.Y();
			float z = m_rotation.Z();

			z += EngineTime::getDeltaTime() * moveSpeed * 0.1f;
			this->SetRotation(x, y, z);
		}
	}

	//std::cout << "key pressed: " << char(key) << std::endl;
}


void EditorCamera::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_right = 0.0f;

	if (key == VK_SHIFT && is_HoldingP)
	{
		is_HoldingP = false;
	}
}

void EditorCamera::onMouseMove(const Point& mouse_pos)
{
	if (InputSystem::get()->getRightMouseDown() && ProjectionType != orthographic)
	{
		InputSystem::get()->setCursorPosition(Point((int)(m_window->Width() / 2.0f), (int)(m_window->Height() / 2.0f)));
		float x = m_rotation.X();
		float y = m_rotation.Y();
		float z = m_rotation.Z();

		float speed = 0.1;
		x += (mouse_pos.m_y - (m_window->Height() / 2.0f)) * EngineTime::getDeltaTime() * speed;
		y += (mouse_pos.m_x - (m_window->Width() / 2.0f)) * EngineTime::getDeltaTime() * speed;
		this->SetRotation(x, y, z);
	}
}


void EditorCamera::onRightMouseDown(const Point& delta_mouse_pos)
{
	InputSystem::get()->showCursor(false);
	::GetCursorPos(&current_mouse_pos);
	std::cout << "Right Mouse Down\n";
}

void EditorCamera::onRightMouseUp(const Point& delta_mouse_pos)
{
	InputSystem::get()->showCursor(true);
	std::cout << "Right Mouse Up\n";
}


void EditorCamera::SetInitialPosition(const Vector3D& newPos)
{
	initialPosition = newPos;
	m_position = newPos;
	this->updateCamera();
}

void EditorCamera::SetInitialRotation(const Vector3D& newRot)
{
	initialRotation = newRot;
	m_rotation = newRot;
	this->updateCamera();
}

void EditorCamera::SetInitialPosition(float x, float y, float z)
{
	initialPosition = Vector3D(x, y, z);
	m_position.SetVector(x, y, z);
	this->updateCamera();
}

void EditorCamera::SetInitialRotation(float x, float y, float z)
{
	initialRotation = Vector3D(x, y, z);
	m_rotation.SetVector(x, y, z);
	this->updateCamera();
}

EditorCamera::~EditorCamera()
{
}
