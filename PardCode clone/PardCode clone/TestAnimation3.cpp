#include "TestAnimation3.h"
#include "EngineTime.h"
#include "Math.h"
#include "Transform.h"

TestAnimation3::TestAnimation3() : Component(Component::script)
{

}

void TestAnimation3::update()
{
	m_delta_scale += EngineTime::getDeltaTime();
	if (m_delta_scale >= 2 * Math::pi()) m_delta_scale = 0;

	Vector3D new_pos = Vector3D::lerp(Vector3D(0, 0, 0), Vector3D(1, 1, 0), abs(sin(m_delta_scale) * 2));
	Vector3D new_scale = Vector3D::lerp(Vector3D::ones(), Vector3D::ones() * 0.25, abs(sin(m_delta_scale)));
	attachedObject->getTransform()->SetPosition(new_pos);
	attachedObject->getTransform()->SetScale(new_scale);
}

TestAnimation3::~TestAnimation3()
{

}