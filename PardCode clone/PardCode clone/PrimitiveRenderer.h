#pragma once
#include "Renderer.h"
#include "RenderingPrerequisite.h"
#include "TextureManager/Texture.h"

enum PRIMITIVE_TYPE { CUBE, PLANE };
class PrimitiveRenderer : public Renderer
{
public:
	PrimitiveRenderer(PRIMITIVE_TYPE primitive, TexturePtr tex);
	virtual void update() override;
	//virtual void draw(AppWindow* window) override;
	void createShaders(vertex* vertex_list, UINT size_list);
	void createCube();
	void createPlane();
	void setTexture(TexturePtr tex);
	~PrimitiveRenderer();

protected:
	VertexBufferPtr m_vb;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	ConstantBufferPtr m_cb;
	IndexBufferPtr m_ib;
	TexturePtr m_texture;
};

