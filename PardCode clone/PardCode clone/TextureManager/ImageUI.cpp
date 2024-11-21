#include "ImageUI.h"
#include "../GraphicsEngine.h"
#include "../Editor UI/imgui-master/imgui.h"

ImageUI::ImageUI(const char* filePath)
{
	ImageUIManager* im = GraphicsEngine::get()->getImageUIManager();
	bool ret = im->LoadTextureFromFile(filePath, &m_srv, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
}

ID3D11ShaderResourceView* ImageUI::getShaderResourceView()
{
	return m_srv;
}

int ImageUI::Width()
{
	return my_image_width;
}

int ImageUI::Height()
{
	return my_image_height;
}

ImageUI::~ImageUI()
{
	m_srv->Release();
}
