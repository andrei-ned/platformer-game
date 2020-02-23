#pragma once
#include <cassert>

template<class T>
class Singleton
{
protected:
	Singleton() {}
	~Singleton() {}
public:
	Singleton(Singleton const &) = delete;
	Singleton& operator=(Singleton const &) = delete;
	static T& get()
	{
		static T* instance;
		if (!instance)
		{
			instance = new T;
		}
		return *instance;
	}
};

