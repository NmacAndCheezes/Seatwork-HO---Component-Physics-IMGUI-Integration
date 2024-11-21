#pragma once
#include "AGameObject.h"
#include <string>

class Component
{
public:
	enum ComponentType { none = -1, script = 0, renderer = 1, physics = 2 };

	Component(ComponentType cType);
	virtual void update() = 0;
	virtual void attachGameObject(AGameObject* obj);
	void detachGameObject();
	AGameObject* const getAttachedGameObject();
	~Component() {}

	std::string getName() { return typeid(this).name(); };

protected:
	AGameObject* attachedObject = nullptr;
	ComponentType m_ComponentType;

private:
	friend class AGameObject;
};

