#pragma once
#include "stb_image.h"
#include <DirectXTex.h>

class ImageUIManager
{
public:
	ImageUIManager();
	~ImageUIManager();
	bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
private:
	bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

};

