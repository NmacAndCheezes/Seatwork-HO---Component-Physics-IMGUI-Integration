#pragma once
#include "Renderer.h"
#include "TextureManager/Texture.h"

class MeshRenderer : public Renderer
{
public:
	MeshRenderer(AMeshPtr meshPtr);
	MeshRenderer(TexturePtr texture, AMeshPtr meshPtr);
	virtual void update();
	//virtual void draw(AppWindow* target) = 0;
	~MeshRenderer();
protected:
	AMeshPtr m_mesh = nullptr;
	VertexShaderPtr m_vs = nullptr;
	PixelShaderPtr m_ps = nullptr;
	ConstantBufferPtr m_cb = nullptr;
	TexturePtr m_texture = nullptr;
};

