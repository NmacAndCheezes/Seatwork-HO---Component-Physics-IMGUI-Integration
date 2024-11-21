#pragma once
#include <memory>
#include "../Resource.h"
#include "../../VertexBuffer.h"
#include "../../IndexBuffer.h"

class AMesh : public Resource
{

public:
	AMesh(const wchar_t* full_path);
	~AMesh();
	virtual const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();
private:
	VertexBufferPtr m_vb;
protected:
	IndexBufferPtr  m_ib;
protected:
	friend class DeviceContext;
};

typedef std::shared_ptr<AMesh> AMeshPtr;
