#pragma once
#include "Camera.h"

class CameraManager
{
public:
	Camera* getCurrentCamera();

	static void initialize();
	static void destroy();
	static CameraManager* get();

	void registerCamera(Camera* cam);
private:
	CameraManager();
	static CameraManager* sharedInstance;
	CameraManager(CameraManager const&) {}
	CameraManager& operator=(CameraManager const&) {};
	~CameraManager();
private:
	Camera* m_cam = NULL;
};

