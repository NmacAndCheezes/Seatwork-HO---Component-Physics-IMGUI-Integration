#include "BaseComponentSystem.h"
#include "../Physics/PhysicsSystem.h"
#include <exception>

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem::BaseComponentSystem()
{
	this->m_ps = new PhysicsSystem();
}

BaseComponentSystem* BaseComponentSystem::get()
{
    return sharedInstance;
}

void BaseComponentSystem::initialize()
{
	if (BaseComponentSystem::sharedInstance) throw std::exception("Base Component System already created");
	BaseComponentSystem::sharedInstance = new BaseComponentSystem();
}


void BaseComponentSystem::destroy()
{
	if (!BaseComponentSystem::sharedInstance) return;
	delete BaseComponentSystem::sharedInstance;
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
    return m_ps;
}

BaseComponentSystem::~BaseComponentSystem()
{
	delete m_ps;
}
