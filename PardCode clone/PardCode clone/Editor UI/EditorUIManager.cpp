#include "EditorUIManager.h"

#include <exception>
#include <Windows.h>
#include "../GraphicsEngine.h"
#include "../RenderSystem.h"
#include "../DeviceContext.h"
#include "CreditsScreen.h"
#include "EColorPickerScreen.h"
#include "EToolBar.h"
#include "EHeirarcyUI.h"
#include "EInspectorUI.h"

EditorUIManager* EditorUIManager::sharedInstance = nullptr;

EditorUIManager::EditorUIManager(HWND hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getRenderSystem()->getID3D11Device(), GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext().get()->getID3D11DeviceContext());
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	EToolBar* tb = new EToolBar();
	m_UIScreenList["Tool Bar"] = tb;

	EHeirarcyUI* h = new EHeirarcyUI();
	m_UIScreenList["Heirarcy"] = h;

	EInspectorUI* i = new EInspectorUI(h);
	m_UIScreenList["Inspector"] = i;
}

void EditorUIManager::initialize(HWND hwnd)
{
	if (EditorUIManager::sharedInstance) throw std::exception("EditorUIManager already created");
	EditorUIManager::sharedInstance = new EditorUIManager(hwnd);
}

void EditorUIManager::update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (auto i : m_UIScreenList)
	{
		if (!i.second->getIsActive()) continue;
		i.second->update();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}

void EditorUIManager::destroy()
{
	if (!EditorUIManager::sharedInstance) return;
	delete EditorUIManager::sharedInstance;
}

EditorUIManager* EditorUIManager::get()
{
	return sharedInstance;
}

AUIScreen* EditorUIManager::getUIScreen(std::string name)
{
	return m_UIScreenList[name];
}

EditorUIManager::~EditorUIManager()
{

}
