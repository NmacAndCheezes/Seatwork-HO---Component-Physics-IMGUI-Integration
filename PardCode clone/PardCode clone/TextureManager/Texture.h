#pragma once
#include "../ResourceManager/Resource.h"
#include <d3d11.h>
class Texture : public Resource
{
public:
	Texture(const wchar_t* full_path);
	~Texture();

private:
	ID3D11Resource* m_texture;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;
private:
	friend class DeviceContext;
};

typedef std::shared_ptr<Texture> TexturePtr;

