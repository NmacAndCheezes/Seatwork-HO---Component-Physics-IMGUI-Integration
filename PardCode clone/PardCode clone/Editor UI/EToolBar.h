#pragma once
#include "CreditsScreen.h"
#include "AUIScreen.h"
#include "EColorPickerScreen.h"
class EToolBar : public AUIScreen
{
public:
	EToolBar();
	virtual void update() override;
	~EToolBar();
};

