#include "ShaderLibrary.h"
#include <exception>
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "VertexShader.h"
#include "PixelShader.h"

ShaderLibrary* ShaderLibrary::sharedInstance = nullptr;

ShaderLibrary* ShaderLibrary::get()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	if (ShaderLibrary::sharedInstance != nullptr) throw std::exception("Graphics Engine already created");
	ShaderLibrary::sharedInstance = new ShaderLibrary();
}


void ShaderLibrary::destroy()
{
	if (!ShaderLibrary::sharedInstance) return;
	delete ShaderLibrary::sharedInstance;
}

ShaderLibrary::ShaderLibrary()
{
	//initialize and load all shaders for use
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	RenderSystem* renderSystem = graphEngine->getRenderSystem();

	ShaderData shaderData;
	renderSystem->compileVertexShader(ShaderNames::BASE_VERTEX_SHADER_NAME().c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[ShaderNames::BASE_VERTEX_SHADER_NAME()] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compilePixelShader(ShaderNames::BASE_PIXEL_SHADER_NAME().c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[ShaderNames::BASE_PIXEL_SHADER_NAME()] = renderSystem->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compileVertexShader(ShaderNames::VERTEX_MESH_LAYOUT_SHADER().c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[ShaderNames::VERTEX_MESH_LAYOUT_SHADER()] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	std::cout << "Shader library initialized. \n";
}

VertexShaderPtr ShaderLibrary::requestVertexShaderData(std::wstring vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(vertexShaderName.c_str(), "vsmain", shaderByteCode, sizeShader);
	return getVertexShader(vertexShaderName);
}

VertexShaderPtr ShaderLibrary::getVertexShader(std::wstring vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL) {
		std::cout << "Vertex shader " << vertexShaderName.c_str() << " not found. Have you initialized it? \n";
	}
	return this->activeVertexShaders[vertexShaderName];
}

PixelShaderPtr ShaderLibrary::getPixelShader(std::wstring pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL) {
		std::cout << "Pixel shader " << pixelShaderName.c_str() << " not found. Have you initialized it? \n";
	}
	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::~ShaderLibrary()
{
	ShaderNames shaderNames;

	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
}
