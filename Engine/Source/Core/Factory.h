#pragma once
#include "Singleton.h"

#include <memory>
#include <map>
#include <string>
#include <iostream>
using namespace std;


class CreatorBase {
public:
	virtual ~CreatorBase() = default;
	virtual unique_ptr<class Object> Create() = 0;
};

template <typename T>
class Creator : public CreatorBase {
public:
	unique_ptr<class Object> Create() override {
		return make_unique<T>();
	}
};

class Factory : public Singleton<Factory> {
public:
	template <typename T>
	void Register(const string& name);

	template <typename T>
	unique_ptr<T> Create(const string& name);

private:
	map<string, unique_ptr<CreatorBase>> m_registry;
};

template<typename T>
inline void Factory::Register(const string& name)
{
	//add creator of type T to registry
	m_registry[name] = make_unique<Creator<T>>();

}

template<typename T>
inline unique_ptr<T> Factory::Create(const string& name)
{
	//check if name is in registry
	if (m_registry.find(name) != m_registry.end()) {
		//if the name is in the registry
		return unique_ptr<T>(dynamic_cast<T*>(m_registry[name]->Create().release()));
	}

	std::cerr << "Could not create factory object: " << name << std::endl;
	//name is not in the registry
	return unique_ptr<T>();
}