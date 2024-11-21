#pragma once
#include <map>
#include <string>
#include "AppWindow.h"
#include "Renderer.h"
#include "AGameObject.h"

class AGameObjectManager
{
public:
	void registerAGameObject(AGameObject* obj);
	void deleteAGameObject(AGameObject* obj);

	void update();

	static void initialize();
	static void destroy();
	static AGameObjectManager* get();

	std::map<std::string, AGameObject*> getObjectList();
private:
	AGameObjectManager();
	static AGameObjectManager* sharedInstance;
	AGameObjectManager(AGameObjectManager const&) {}
	AGameObjectManager& operator=(AGameObjectManager const&) {};
	~AGameObjectManager();

private:
	std::map<std::string, AGameObject*> m_object_list;

private:
	friend class AGameObject;
};

