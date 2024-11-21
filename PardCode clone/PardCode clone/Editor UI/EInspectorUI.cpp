#include "EInspectorUI.h"
#include "EHeirarcyUI.h"
#include "../Transform.h"
#include "../AGameObject.h"
#include "../InputSystem.h"
#include "../EditorStates/EditorActions/EditorActionHistory.h"


EInspectorUI::EInspectorUI(EHeirarcyUI* heirarcy) : m_heirarcy(heirarcy)
{
}

void EInspectorUI::update()
{
	ImGui::Begin("Inspector");
	if (m_heirarcy->getSelectedObj() != nullptr)
	{
		//std::cout << ImGui::GetMouseClickedCount(ImGuiButtonFlags_MouseButtonLeft) << std::endl;
		if (ImGui::IsMouseDown(ImGuiButtonFlags_None) && !mouseDown)
		{
			EditorActionHistory::get()->RecordAction(m_heirarcy->getSelectedObj());
			mouseDown = true;
		}
		else if(!ImGui::IsMouseDown(ImGuiButtonFlags_None) && mouseDown)
		{
			EditorActionHistory::get()->CheckIfSimilar(m_heirarcy->getSelectedObj());
			mouseDown = false;
		}

		AGameObject* selected = m_heirarcy->getSelectedObj();
		Transform* t = selected->getTransform();
		pos[0] = t->getTransformMatrix().getTranslation().X();
		pos[1] = t->getTransformMatrix().getTranslation().Y();
		pos[2] = t->getTransformMatrix().getTranslation().Z();

		rot[0] = t->localRotation().X();
		rot[1] = t->localRotation().Y();
		rot[2] = t->localRotation().Z();

		scale[0] = t->localScale().X();
		scale[1] = t->localScale().Y();
		scale[2] = t->localScale().Z();
#if 0
		pos[0] = t->localPosition().X();
		pos[1] = t->localPosition().Y();
		pos[2] = t->localPosition().Z();

		rot[0] = t->localRotation().X();
		rot[1] = t->localRotation().Y();
		rot[2] = t->localRotation().Z();

		scale[0] = t->localScale().X();
		scale[1] = t->localScale().Y();
		scale[2] = t->localScale().Z();
#endif
		bool isActive = selected->getActive();
		ImGui::Checkbox("is Active", &isActive);
		ImGui::SameLine();
		ImGui::Text(selected->getId().c_str());

		ImGui::DragFloat3("Position", pos);
		ImGui::DragFloat3("Rotation", rot);
		ImGui::DragFloat3("Scale", scale);

		selected->setActive(isActive);
		selected->getTransform()->SetLocalPosition(Vector3D(pos[0], pos[1], pos[2]));
		selected->getTransform()->SetLocalRotation(Vector3D(rot[0], rot[1], rot[2]));
		selected->getTransform()->SetLocalScale(Vector3D(scale[0], scale[1], scale[2]));
	}
	ImGui::End();
}

EInspectorUI::~EInspectorUI()
{
	delete m_heirarcy;
}
