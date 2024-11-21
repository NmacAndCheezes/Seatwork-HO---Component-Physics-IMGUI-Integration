#include "PrimitiveRenderer.h"
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

#include <iostream>
#include "ShaderLibrary.h"

PrimitiveRenderer::PrimitiveRenderer(PRIMITIVE_TYPE primitive, TexturePtr tex) : m_texture(tex), Renderer()
{
	switch (primitive)
	{
	case PLANE:
		createPlane();
		break;
	case CUBE:
		createCube();
		break;
	}	
}

void PrimitiveRenderer::update()
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
	renderSystem->getImmediateDeviceContext()->setTexture(m_ps, m_texture);
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	renderSystem->getImmediateDeviceContext()->setVertexShader(m_vs);
	renderSystem->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	renderSystem->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	renderSystem->getImmediateDeviceContext()->setIndexBuffer(m_ib);


	// FINALLY DRAW THE TRIANGLE
	renderSystem->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void PrimitiveRenderer::createCube()
{

	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }


	};
	UINT size_list = ARRAYSIZE(vertex_list);


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	createShaders(vertex_list, size_list);

	std::cout << "Initalized Cube" << std::endl;
}

void PrimitiveRenderer::createShaders(vertex* vertex_list, UINT size_list)
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	m_vs = ShaderLibrary::get()->requestVertexShaderData(ShaderNames::BASE_VERTEX_SHADER_NAME(), &shader_byte_code, &size_shader);
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, (UINT)size_shader);

	m_ps = ShaderLibrary::get()->getPixelShader(ShaderNames::BASE_PIXEL_SHADER_NAME());

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void PrimitiveRenderer::createPlane()
{
	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(0.5f,-0.5f,-0.5f)},
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	vertex vertex_list[] =
	{
		{ position_list[3],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },
	};
	UINT size_list = ARRAYSIZE(vertex_list);


	unsigned int index_list[] =
	{
		0,1,2,
		2,3,0
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	createShaders(vertex_list, size_list);

	std::cout << "Initalized Plane" << std::endl;
}

void PrimitiveRenderer::setTexture(TexturePtr tex)
{
	m_texture = tex;
}

PrimitiveRenderer::~PrimitiveRenderer()
{
}
