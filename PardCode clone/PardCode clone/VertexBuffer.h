#pragma once
#include <d3d11.h>
#include "RenderingPrerequisite.h"

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader,
		RenderSystem* system);
	UINT getSizeVertexList();
	~VertexBuffer();
protected:
	UINT m_size_vertex;
	UINT m_size_list;
protected:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	RenderSystem* m_system = nullptr;
protected:
	friend class DeviceContext;
};