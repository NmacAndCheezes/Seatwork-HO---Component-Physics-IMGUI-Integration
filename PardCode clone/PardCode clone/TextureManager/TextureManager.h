#pragma once
#include "../ResourceManager/ResourceManager.h"
#include "Texture.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	TexturePtr createTextureFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createFromResourceFromFileConcrete(const wchar_t* file_path) override;
};

