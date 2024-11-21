#pragma once

#include "VertexBuffer.h"
class VertexColorBuffer : public VertexBuffer
{
public:
	VertexColorBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader,
		RenderSystem* system);
	~VertexColorBuffer();
};

