#include "Component.h"
#include "AGameObject.h"

Component::Component(ComponentType cType)
{
	m_ComponentType = cType;
}

void Component::attachGameObject(AGameObject* obj)
{
	attachedObject = obj;
}

void Component::detachGameObject()
{
	attachedObject = nullptr;
}

AGameObject* const Component::getAttachedGameObject()
{
	return attachedObject;
}
