#include "AGameObject.h"
#include "Component.h"
#include "AGameObjectManager.h"
#include "ECS Systems/BaseComponentSystem.h"
#include "Physics/PhysicsSystem.h"
#include "Physics/PhysicsComponent.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"

AGameObject::AGameObject() : m_transform(new Transform(this))
{
	AGameObjectManager::get()->registerAGameObject(this);	
}

AGameObject::AGameObject(std::string name) : m_name(name), m_transform(new Transform(this))
{
	AGameObjectManager::get()->registerAGameObject(this);
}

void AGameObject::update()
{
	if (!this->m_isActive) return;

	for (auto c : m_component_list)
	{
		if (c) 
		{
			c->update(); // Check if component is valid
		}
	}

	
	//std::cout << "Position: " << position().X() << ", " << position().Y() << ", " << position().Z() << ", " << std::endl;
	//std::cout << "Rotation: " << rotation().X() << ", " << rotation().Y() << ", " << rotation().Z() << ", " << std::endl;
	//std::cout << "Scale: " << scale().X() << ", " << scale().Y() << ", " << scale().Z() << ", " << std::endl;
}

void AGameObject::attachComponent(Component* component)
{
	component->attachGameObject(this);
	switch (component->m_ComponentType)
	{
	case Component::physics:
		BaseComponentSystem::get()->getPhysicsSystem()->registerComponent((PhysicsComponent*)component);
		break;
	case Component::renderer:
		GraphicsEngine::get()->getRenderSystem()->registerComponent((Renderer*)component);
	default:
		m_component_list.push_back(component);
		std::cout << "Attached " << component->getName() << " to " << m_name << std::endl;
	}
	
}

void AGameObject::detachComponent(Component* component)
{
	switch (component->m_ComponentType)
	{
	default:
		auto it = std::find(m_component_list.begin(), m_component_list.end(), component);
		if (it == m_component_list.end()) return;

		component->detachGameObject();
		m_component_list.remove(component);
		std::cout << "Detached " << component->getName() << " from " << m_name << std::endl;
	}
	
}

void AGameObject::setId(int id)
{
	m_id = std::to_string(id) + m_name;
}

std::string AGameObject::getId()
{
	return m_id;
}

void AGameObject::setName(std::string name)
{
	m_name = name;
}

std::string AGameObject::getName()
{
	return m_name;
}

AGameObject::~AGameObject()
{
	delete m_transform;
	m_children.clear();
	m_component_list.clear();
}

void AGameObject::setActive(bool isActive)
{
	this->m_isActive = isActive;
}

bool AGameObject::getActive()
{
	return m_isActive;
}

Transform* AGameObject::getTransform()
{
	return m_transform;
}

void AGameObject::attachChild(AGameObject* child)
{
	if (child == this || child == nullptr) return;

	if (child->getParent() != nullptr)
	{
		child->getParent()->detachChild(child);
	}

	this->m_children.push_back(child);
	child->setParent(this);
	child->setActive(m_isActive);

	//child->getTransform()->RecalculateChildTransformWithParent(this->getTransform());
}

void AGameObject::detachChild(AGameObject* child)
{
	if (child == this || child == nullptr) return;

	this->m_children.remove(child);

	child->setParent(NULL);
	//child->gettransform->RecalculateChildTransformWithoutParent();

	//this->childList.erase(std::remove(this->childList.begin(), this->childList.end(), child), this->childList.end());
}

void AGameObject::setParent(AGameObject* parent)
{
	m_parent = parent;
}

AGameObject* AGameObject::getParent()
{
	return m_parent;
}
