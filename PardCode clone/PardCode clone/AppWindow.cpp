/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2022, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/


#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "AGameObjectManager.h"
#include "Cube.h"
#include "Rotator.h"
#include "Plane.h"
#include "EditorCamera.h"
#include "CameraManager.h"
#include "InputSystem.h"
#include "Math.h"
#include "TestAnimation3.h"
#include "WarpCubeToPlane.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "Editor UI/EditorUIManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "ShaderLibrary.h"
#include "Physics/PhysicsSystem.h"
#include "ECS Systems/BaseComponentSystem.h"
#include "EditorStates/EditorBackend.h"
#include "EditorStates/EditorActions/EditorActionHistory.h"

AppWindow::AppWindow()
{
	EditorBackend::initialize();
	EditorActionHistory::initialize();
	InputSystem::initialize();
	GraphicsEngine::initialize();
	ShaderLibrary::initialize();
	CameraManager::initialize();
	EngineTime::initialize();
	AGameObjectManager::initialize();
	BaseComponentSystem::initialize();
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	EditorCamera* eCam = new EditorCamera(this);
	eCam->SetPosition(3.78148, 6.62727, -4.19345);
	eCam->SetRotation(0.697706, -0.763867, 0);
	eCam->setViewType(0);
	CameraManager::get()->registerCamera(eCam);
	InputSystem::get()->addListner(eCam);

	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, Width(), Height());


	
#if 1
	TexturePtr m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"./Assets/Textures/brick.png");
	for (int i = 0; i < 10; i++)
	{
		float x = ((float(rand()) / float(RAND_MAX)) * 1.5f) - 0.75f;
		float y = ((float(rand()) / float(RAND_MAX)) * 1.5f) - 0.75f;
		float z = ((float(rand()) / float(RAND_MAX)) * 1.5f);


		Cube* cube = new Cube(m_wood_tex);
		cube->getTransform()->SetLocalPosition(Vector3D(x, y + 6.0f, z));
		cube->getTransform()->SetLocalRotation(Vector3D(0, 0, 0));
		//cube->getTransform()->SetLocalScale(Vector3D(0.2f, 0.2f, 0.2f));
	}
#endif
	EditorUIManager::initialize(this->m_hwnd);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->m_swap_chain,
		0, 
		0.3f,
		0.4f, 
		1
	);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(Width(), Height());

	//CameraManager::get()->getCurrentCamera()->updateCamera();
	InputSystem::get()->update();
	if(EditorBackend::get()->getState() == EditorBackend::PLAY())
		BaseComponentSystem::get()->getPhysicsSystem()->updateAllComponents();

	GraphicsEngine::get()->getRenderSystem()->renderAll();

	AGameObjectManager::get()->update();
	EditorUIManager::get()->update();
	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	EditorUIManager::destroy();
	BaseComponentSystem::destroy();
	AGameObjectManager::destroy();
	CameraManager::destroy();
	ShaderLibrary::destroy();
	GraphicsEngine::destroy();
	InputSystem::destroy();
	EditorActionHistory::destroy();
	EditorBackend::destroy();
}
