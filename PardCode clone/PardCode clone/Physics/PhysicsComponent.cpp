#include "PhysicsComponent.h"
#include "../EngineTime.h"
#include "../Matrix4x4.h"
#include "../ECS Systems/BaseComponentSystem.h"
#include "PhysicsSystem.h"
PhysicsComponent::PhysicsComponent(std::string name) : Component(Component::physics)
{
	
}

void PhysicsComponent::attachGameObject(AGameObject* obj)
{
	Component::attachGameObject(obj);
	BaseComponentSystem::get()->getPhysicsSystem()->registerComponent(this);
	//Init();
}

void PhysicsComponent::Init()
{
	//whenever a new physics component is initialized. Register to physics system
	reactphysics3d::PhysicsCommon* physicsCommon = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsCommon();
	reactphysics3d::PhysicsWorld* physicsWorld = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsWorld();

	// Create a rigid body in the world
	Vector3D scale = this->attachedObject->getTransform()->localScale();
	scale.printVector("Phys Com");
	reactphysics3d::Transform transform; transform.setFromOpenGL(this->attachedObject->getTransform()->getPhysicsLocalMatrix());
	reactphysics3d::BoxShape* boxShape = physicsCommon->createBoxShape(reactphysics3d::Vector3(scale.X() / 2, scale.Y() / 2, scale.Z() / 2)); //half extent
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	setBodyType(bodyType);
}

PhysicsComponent::~PhysicsComponent()
{
	delete rigidBody;
}

void PhysicsComponent::update()
{
	const reactphysics3d::Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);
	this->attachedObject->getTransform()->setPhysicsMatrix(matrix);
}

#if 0
reactphysics3d::RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}
#endif

void PhysicsComponent::setBodyType(reactphysics3d::BodyType bt)
{
	bodyType = bt;

	if(rigidBody != NULL)
		rigidBody->setType(bt);
}
