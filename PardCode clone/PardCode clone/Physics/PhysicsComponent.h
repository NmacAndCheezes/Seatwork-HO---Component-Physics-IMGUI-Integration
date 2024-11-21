#pragma once
#include "../AGameObject.h"
#include "../Component.h"
#include <reactphysics3d/reactphysics3d.h>
#include <string>

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(std::string name);
	void update() override;
	virtual void attachGameObject(AGameObject* obj) override;
	void Init();
	~PhysicsComponent();

	//reactphysics3d::RigidBody* getRigidBody();
	void setBodyType(reactphysics3d::BodyType bt);
	bool getEnabledGravity() { return this->enableGravity; }
	void setEnabledGravity(bool enabled) { enableGravity = enabled; }
private:
	float mass = 1000.0f; //in kilograms
	bool enableGravity = true;
	reactphysics3d::RigidBody* rigidBody;
	reactphysics3d::BodyType bodyType = reactphysics3d::BodyType::DYNAMIC;
};

