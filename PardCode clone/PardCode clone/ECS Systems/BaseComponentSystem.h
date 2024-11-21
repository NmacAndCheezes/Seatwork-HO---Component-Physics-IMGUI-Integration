#pragma once
class PhysicsSystem;
class BaseComponentSystem
{
public:
	static BaseComponentSystem* get();
	static void initialize();
	static void destroy();

	PhysicsSystem* getPhysicsSystem();

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&) {};
	BaseComponentSystem& operator*(BaseComponentSystem const&) {};
	static BaseComponentSystem* sharedInstance;

	PhysicsSystem* m_ps;

};

