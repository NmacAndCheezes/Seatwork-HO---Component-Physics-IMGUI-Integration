#include "MeshRenderer.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DeviceContext.h"
#include "CameraManager.h"
#include "RenderSystem.h"
#include "Transform.h"
#include "ShaderLibrary.h"

MeshRenderer::MeshRenderer(AMeshPtr meshPtr) : Renderer()
{
	m_mesh = meshPtr;

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"./VertexColorShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();


	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"./PixelShaderColor.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

MeshRenderer::MeshRenderer(TexturePtr texture, AMeshPtr meshPtr) : Renderer()
{
	m_texture = texture;
	m_mesh = meshPtr;

	m_vs = ShaderLibrary::get()->getVertexShader(ShaderNames::BASE_VERTEX_SHADER_NAME());
	m_ps = ShaderLibrary::get()->getPixelShader(ShaderNames::BASE_PIXEL_SHADER_NAME());

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void MeshRenderer::update()
{
	constant cbData = {};
	cbData.m_world = this->attachedObject->getTransform()->getTransformMatrix();
	//cbData.m_world.printMatrix();

#pragma region Camera
	cbData.m_view = CameraManager::get()->getCurrentCamera()->getViewMatrix();
	cbData.m_proj = CameraManager::get()->getCurrentCamera()->getProjectionMatrix();
#pragma endregion

	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	DeviceContextPtr deviceContext = renderSystem->getImmediateDeviceContext();
	this->m_cb->update(deviceContext, &cbData);
	//std::cout << "World:\n"; cbData.m_world.printMatrix(); std::cout << std::endl;
	//std::cout << "View:\n"; cbData.m_view.printMatrix(); std::cout << std::endl;
	//std::cout << "Proj:\n"; cbData.m_proj.printMatrix(); std::cout << std::endl;
	renderSystem->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	renderSystem->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET TEXTURE
	if (m_texture != nullptr)
	{
		renderSystem->getImmediateDeviceContext()->setTexture(m_ps, m_texture);
	}
	
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	renderSystem->getImmediateDeviceContext()->setVertexShader(m_vs);
	renderSystem->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	renderSystem->getImmediateDeviceContext()->setVertexBuffer(m_mesh.get()->getVertexBuffer());
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	renderSystem->getImmediateDeviceContext()->setIndexBuffer(m_mesh.get()->getIndexBuffer());


	// FINALLY DRAW THE TRIANGLE
	renderSystem->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh.get()->getIndexBuffer()->getSizeIndexList(), 0, 0);
}

MeshRenderer::~MeshRenderer()
{
}
