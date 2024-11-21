#pragma once
#include "../ResourceManager.h"
#include "AMesh.h"
#include "MeshColor.h"

class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	AMeshPtr createMeshFromFile(const wchar_t* file_path);
	MeshColorPtr createMeshColorFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createFromResourceFromFileConcrete(const wchar_t* file_path) override;
};

