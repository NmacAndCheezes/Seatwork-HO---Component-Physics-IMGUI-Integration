#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>
#include "PhysicsComponent.h"

class PhysicsSystem
{
public:
	PhysicsSystem();

	void registerComponent(PhysicsComponent* component);
	void unregisterComponent(PhysicsComponent* component);
	void unregisterComponentByName(std::string name);
	PhysicsComponent* findComponentByName(std::string name);
	std::vector<PhysicsComponent*> getAllComponents();

	void resetAllComponents();
	void updateAllComponents();
	reactphysics3d::PhysicsWorld* getPhysicsWorld();
	reactphysics3d::PhysicsCommon* getPhysicsCommon();

	~PhysicsSystem();
private:
	reactphysics3d::PhysicsCommon* m_pc = nullptr;
	reactphysics3d::PhysicsWorld* m_pw = nullptr;

	std::unordered_map<std::string, PhysicsComponent*> componentTable;
	std::vector<PhysicsComponent*> componentList;
};

