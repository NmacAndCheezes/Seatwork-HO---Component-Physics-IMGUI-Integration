#include "../AGameObjectManager.h"
#include "EHeirarcyUI.h"
#include "../AGameObject.h"

EHeirarcyUI::EHeirarcyUI()
{

}

void EHeirarcyUI::update()
{
	if (!isActive) return;

	ImGui::Begin("Heirarcy");

	for (auto obj : AGameObjectManager::get()->getObjectList())
	{
		if (ImGui::Button(obj.second->getId().c_str()))
		{
			m_selected_gObj = obj.second;
			//std::cout << "Selected: " << m_selected_gObj->getName() << std::endl;
		}
	}

	ImGui::End();
}

AGameObject* EHeirarcyUI::getSelectedObj()
{
	return m_selected_gObj;
}

EHeirarcyUI::~EHeirarcyUI()
{
	delete m_selected_gObj;
}