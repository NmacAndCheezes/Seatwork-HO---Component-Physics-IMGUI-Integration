#include "AGameObjectManager.h"
#include "AGameObject.h"

AGameObjectManager* AGameObjectManager::sharedInstance = nullptr;

AGameObjectManager::AGameObjectManager()
{

}

void AGameObjectManager::registerAGameObject(AGameObject* obj)
{
	obj->setId(m_object_list.size());
	m_object_list[obj->getId()] = obj;
}

std::map<std::string, AGameObject*> AGameObjectManager::getObjectList()
{
	return m_object_list;
}

void AGameObjectManager::deleteAGameObject(AGameObject* obj)
{
	m_object_list.erase(obj->getId());
	delete obj;
}


void AGameObjectManager::update()
{
	for (auto obj : m_object_list)
	{
		if (!obj.second->getActive()) continue;
		obj.second->update();
	}
}

void AGameObjectManager::initialize()
{
	if (AGameObjectManager::sharedInstance) throw std::exception("AGameObjectManager already created");
	AGameObjectManager::sharedInstance = new AGameObjectManager();
}


void AGameObjectManager::destroy()
{
	if (!AGameObjectManager::sharedInstance) return;
	delete AGameObjectManager::sharedInstance;
}

AGameObjectManager* AGameObjectManager::get()
{
	static AGameObjectManager manager;
	return &manager;
}

AGameObjectManager::~AGameObjectManager()
{

}
