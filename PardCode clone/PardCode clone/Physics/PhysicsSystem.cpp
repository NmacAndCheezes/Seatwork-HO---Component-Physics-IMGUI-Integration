#include "PhysicsSystem.h"
#include <exception>
#include "../EngineTime.h"

PhysicsSystem::PhysicsSystem()
{
	try
	{
		this->m_pc = new reactphysics3d::PhysicsCommon();
		reactphysics3d::PhysicsWorld::WorldSettings settings;
		settings.defaultVelocitySolverNbIterations = 50;
		settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
		this->m_pw = this->m_pc->createPhysicsWorld(settings);
		std::cout << "Successfully created physics world. \n";
	}
	catch (...)
	{
		throw std::exception("Physics System not created successfully");
	}
}

void PhysicsSystem::resetAllComponents()
{
	this->m_pc->destroyPhysicsWorld(m_pw);

	reactphysics3d::PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
	this->m_pw = this->m_pc->createPhysicsWorld(settings);
	std::cout << "Successfully created physics world. \n";

	for (auto i : this->componentList)
	{
		i->Init();
	}
}

void PhysicsSystem::updateAllComponents()
{
	//do not update during first frame. Delta time is still 0.
	if (EngineTime::getDeltaTime() > 0.0f) {
		//update physics world
		this->m_pw->update(EngineTime::getDeltaTime());
		for (int i = 0; i < this->componentList.size(); i++) {
			this->componentList[i]->update();
		}
	}
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	std::cout << "Registering Physics component: " << component->getName() << "\n";
	this->componentTable[component->getName()] = component;
	this->componentList.push_back(component);
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	std::cout << "Unregistering Physics component: " << component->getName() << "\n";

	if (this->componentTable[component->getName()] != NULL) {
		this->componentTable.erase(component->getName());
		int index = -1;
		for (int i = 0; i < this->componentList.size(); i++) {
			if (this->componentList[i] == component) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			this->componentList.erase(this->componentList.begin() + index);
		}
	}
	else {
		std::cout << "Component " << component->getName() << " not registered in physics component. \n";
	}
}

void PhysicsSystem::unregisterComponentByName(std::string name)
{
	if (this->componentTable[name] != NULL) {
		this->unregisterComponent(this->componentTable[name]);
	}
}

reactphysics3d::PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->m_pw;
}

reactphysics3d::PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->m_pc;
}
PhysicsSystem::~PhysicsSystem()
{
	if (m_pw != nullptr) {
		m_pc->destroyPhysicsWorld(m_pw);
	}
}
