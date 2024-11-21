#include "CameraManager.h"
#include "EditorCamera.h"

CameraManager* CameraManager::sharedInstance = nullptr;

CameraManager::CameraManager()
{
}

Camera* CameraManager::getCurrentCamera()
{
	return m_cam;
}

void CameraManager::initialize()
{
	CameraManager::sharedInstance = new CameraManager();
}

void CameraManager::destroy()
{
	if (!CameraManager::sharedInstance) return;
	delete CameraManager::sharedInstance;
}

void CameraManager::registerCamera(Camera* cam)
{
	m_cam = cam;
}

CameraManager* CameraManager::get()
{
	return sharedInstance;
}

CameraManager::~CameraManager()
{
	m_cam = NULL;
}
