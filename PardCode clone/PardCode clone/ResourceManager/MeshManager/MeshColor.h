#pragma once
#include "AMesh.h"
#include "../../VertexColorBuffer.h"
#include "../../Vector3D.h"
class MeshColor : public AMesh
{
public:
	class VertexColor
	{
	public:
		VertexColor(const Vector3D& pos, const Vector3D& color)
		{
			m_position = pos;
			m_color = color;
		}
		~VertexColor() = default;
	public:
		Vector3D m_position;
		Vector3D m_color;
	};

public:
	MeshColor(const wchar_t* full_path);
	~MeshColor();
	virtual const VertexBufferPtr& getVertexBuffer() override;

private:
	VertexColorBuffer* m_vbColor;
};

typedef std::shared_ptr<MeshColor> MeshColorPtr;

