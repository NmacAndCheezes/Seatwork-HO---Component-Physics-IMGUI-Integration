#pragma once
#include <string>
#include <unordered_map>
#include "RenderingPrerequisite.h"

class ShaderNames {
public:
	//vertex shader names
	static const std::wstring BASE_VERTEX_SHADER_NAME() { return L"VertexShader.hlsl"; }
	static const std::wstring VERTEX_MESH_LAYOUT_SHADER() { return L"VertexMeshLayoutShader.hlsl"; }

	//pixel shader names
	static const std::wstring BASE_PIXEL_SHADER_NAME() { return L"PixelShader.hlsl"; };
	//const String TEXTURED_PIXEL_SHADER_NAME = L"TexturedPixelShader.hlsl";
};

class ShaderLibrary
{
public:
	class ShaderData {
	public:
		void* shaderByteCode = NULL;
		size_t sizeShader = 0;
	};

	static ShaderLibrary* get();
	static void initialize();
	static void destroy();

	VertexShaderPtr requestVertexShaderData(std::wstring vertexShaderName, void** shaderByteCode, size_t* sizeShader); //since shader byte code gets dereferenced for some reason if stored in a hash table. request manually.
	
	VertexShaderPtr getVertexShader(std::wstring vertexShaderName);
	PixelShaderPtr getPixelShader(std::wstring pixelShaderName);

private:
	ShaderLibrary();
	~ShaderLibrary();
	ShaderLibrary(ShaderLibrary const&) {};             // copy constructor is private
	ShaderLibrary& operator=(ShaderLibrary const&) {};  // assignment operator is private*/
	static ShaderLibrary* sharedInstance;

	std::unordered_map<std::wstring, VertexShaderPtr> activeVertexShaders;
	std::unordered_map<std::wstring, PixelShaderPtr> activePixelShaders;

};

