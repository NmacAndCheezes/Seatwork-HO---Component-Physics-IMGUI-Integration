#pragma once
#include "AUIScreen.h"

class EColorPickerScreen : public AUIScreen
{
public:
	EColorPickerScreen();
	virtual void update() override;
	~EColorPickerScreen();

private:
	float colors[3] { 1, 1, 1};
};

