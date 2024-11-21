#pragma once
#include <unordered_map>
#include <string>
#include "Resource.h"
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	ResourcePtr createResourceFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createFromResourceFromFileConcrete(const wchar_t* file_path) = 0;
private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
};


