#pragma once


template<typename T>
class Singleton
{
public:
	Singleton(const Singleton& other) = delete;
	Singleton& operator = (const Singleton& other) = delete;

	static T& instance()
	{
		static T instance;
		return instance;
	}

protected:
	Singleton() = default;
};