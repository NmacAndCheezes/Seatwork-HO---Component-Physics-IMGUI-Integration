#pragma once
#include <d3d11.h>
#include "ImageUIManager.h"
#include  "../GraphicsEngine.h"

class ImageUI
{
public:
	ImageUI(const char* filePath);

	ID3D11ShaderResourceView* getShaderResourceView();
	int Width();
	int Height();
	~ImageUI();

private:
	int my_image_width = 0;
	int my_image_height = 0;
	ID3D11ShaderResourceView* m_srv;
};

