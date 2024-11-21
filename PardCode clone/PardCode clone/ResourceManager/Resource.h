#pragma once
#include <memory>
#include <string>
class Resource
{
public:
	Resource(const wchar_t* full_path);
	virtual ~Resource();
protected:
	std::wstring m_full_path;
};

typedef std::shared_ptr<Resource> ResourcePtr;
