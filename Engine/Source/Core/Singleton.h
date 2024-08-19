#pragma once


template<typename T>
class Singleton
{
public:
	Singleton(const Singleton& other) = delete;
	Singleton& operator = (const Singleton& other) = delete;

	static T& Instance()
	{
		static T Instance;
		return Instance;
	}

protected:
	Singleton() = default;
};