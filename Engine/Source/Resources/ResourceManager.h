#pragma once

#include "Resource.h"
#include "Core/Singleton.h"
#include "Core/EString.h"

#include <map>
#include <iostream>

class ResourceManager : public Singleton<ResourceManager>
{
public:
	void Clear() { m_resources.clear(); }

	template<typename T, typename ... TArgs>
	res_t<T> Get(const std::string& name, TArgs... args);

	friend class Singleton;

	ResourceManager() = default;
protected:

private:
	std::map<std::string, res_t<Resource>> m_resources;
};

template<typename T, typename ... TArgs>
inline res_t<T> ResourceManager::Get(const std::string& name, TArgs... args)
{
	std::string lowername = ToLower(name);

	// find resources in resource manager
	if (m_resources.find(lowername) != m_resources.end())
	{
		// return resource
		return std::dynamic_pointer_cast<T> (m_resources[lowername]);
	}

	// resource not found, create resource
	res_t<T> resource = std::make_shared<T>();
	if (!resource->Create(lowername, args...))
	{
		// resource not created
		std::cerr << "Could not create resource: " << lowername << std::endl;
		return res_t<T>();
	};

	// add resource to resource manager
	m_resources[lowername] = resource;
	return resource;
}
