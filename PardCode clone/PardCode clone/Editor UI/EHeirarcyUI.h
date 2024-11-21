#pragma once
#include "AUIScreen.h"
#include "../AGameObject.h"

class EHeirarcyUI : public AUIScreen
{
public:
	EHeirarcyUI();
	virtual void update() override;
	~EHeirarcyUI();

	AGameObject* getSelectedObj();
private:
	AGameObject* m_selected_gObj = nullptr;
};
