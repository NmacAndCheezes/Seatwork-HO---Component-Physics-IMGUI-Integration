#pragma once
#include "AUIScreen.h"
#include  "../GraphicsEngine.h"
#include "../TextureManager/ImageUI.h"

class CreditsScreen : public AUIScreen
{
public:
	CreditsScreen();
	virtual void update() override;
	~CreditsScreen();

private:
	ImageUI* img;
};

