#include "MeshManager.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

AMeshPtr MeshManager::createMeshFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<AMesh>(createResourceFromFile(file_path));
}

MeshColorPtr MeshManager::createMeshColorFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<MeshColor>(createResourceFromFile(file_path));
}

Resource* MeshManager::createFromResourceFromFileConcrete(const wchar_t* file_path)
{
	AMesh* mesh = nullptr;
	try
	{
		mesh = new AMesh(file_path);
	}
	catch (...) {}
	return mesh;
}
