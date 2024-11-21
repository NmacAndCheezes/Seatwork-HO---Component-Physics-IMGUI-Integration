#include "EToolBar.h"
#include "EditorUIManager.h"
#include "../AGameObject.h"
#include "../MeshRenderer.h"
#include "../ResourceManager/MeshManager/MeshColor.h"
#include "../Cube.h"
#include "../Physics/PhysicsComponent.h"
#include "../EditorStates/EditorBackend.h"
#include "../EditorStates/EditorActions/EditorActionHistory.h"

EToolBar::EToolBar()
{
}

void EToolBar::update()
{
	if (ImGui::BeginMainMenuBar())
	{
		TexturePtr m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"./Assets/Textures/brick.png");
		if (ImGui::BeginMenu("Create")) {
			if(ImGui::BeginListBox("Spawn"))
			{
				if (ImGui::Selectable("Teapot")) {
					AMeshPtr m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"./Assets/Meshes/teapot.obj");

					AGameObject* obj = new AGameObject("Teapot");
					MeshRenderer* mRend = new MeshRenderer(m_wood_tex, m_mesh);
					obj->attachComponent(mRend);
					obj->setActive(true);
				}
				if (ImGui::Selectable("Bunny")) {

					AMeshPtr m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"./Assets/Meshes/bunny.obj");

					AGameObject* obj = new AGameObject("Bunny");
					MeshRenderer* mRend = new MeshRenderer(m_wood_tex, m_mesh);
					obj->attachComponent(mRend);
					obj->setActive(true);
				}
				if (ImGui::Selectable("Armadillo")) {
					AMeshPtr m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"./Assets/Meshes/armadillo.obj");

					AGameObject* obj = new AGameObject("Armadillo");
					MeshRenderer* mRend = new MeshRenderer(m_wood_tex, m_mesh);
					obj->attachComponent(mRend);
					obj->setActive(true);
				}
				if (ImGui::Selectable("Physics Cubes")) {
					TexturePtr m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"./Assets/Textures/brick.png");
					for (int i = 0; i < 10; i++)
					{
						Cube* cube;
						cube = new Cube(m_wood_tex);
						cube->getTransform()->SetLocalPosition(Vector3D(0, 6, 0));
						cube->attachComponent(new PhysicsComponent("Cube Physics"));
					}
				}
				if (ImGui::Selectable("Physics Plane"))
				{
#if 1
					TexturePtr m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"./Assets/Textures/brick.png");

#if 1
					m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"./Assets/Textures/sand.jpg");
					Cube* plane = new Cube(m_wood_tex);
					plane->getTransform()->SetRotation(Vector3D(0, 0, 0));
					plane->getTransform()->SetScale(Vector3D(32, 2, 32));
					PhysicsComponent* pc = new PhysicsComponent("Plane Physics");
					plane->attachComponent(pc);
					pc->setBodyType(reactphysics3d::BodyType::STATIC);
#endif
#endif
				}
				ImGui::EndListBox();
			}
			
			ImGui::EndMenu();
		}
		else if (ImGui::BeginMenu("Play/Stop"))
		{
			if (ImGui::BeginListBox(" "))
			{
				if (ImGui::Selectable("Play") && EditorBackend::get()->getState() != EditorBackend::PLAY)
				{
					if(EditorBackend::get()->getState() != EditorBackend::PAUSE)
						EditorActionHistory::get()->RecordEditStates();

					EditorBackend::get()->setState(EditorBackend::PLAY);
				}
				else if (ImGui::Selectable("Pause"))
				{
					EditorBackend::get()->setState(EditorBackend::PAUSE);
				}
				else if (ImGui::Selectable("Stop") && EditorBackend::get()->getState() != EditorBackend::EDIT)
				{
					EditorActionHistory::get()->SetToEditState();
					EditorBackend::get()->setState(EditorBackend::EDIT);
				}
				ImGui::EndListBox();
			}
			
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("<- / ->"))
		{
			if (ImGui::BeginListBox("Undo / Redo"))
			{
				if (ImGui::Selectable("Undo"))
				{
					EditorActionHistory::get()->Undo();
				}
				else if (ImGui::Selectable("Redo"))
				{
					EditorActionHistory::get()->Redo();
				}
				ImGui::EndListBox();
			}

			ImGui::EndMenu();
		}
		
		
		ImGui::EndMainMenuBar();
	}
}

EToolBar::~EToolBar()
{
}
