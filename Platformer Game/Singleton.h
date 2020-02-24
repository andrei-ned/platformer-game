#pragma once
#include <cassert>
#include <memory>

// Template for singleton design pattern
// Use via inheritance: class Foo : public Singleton<Foo> { ... }
// Then simply use Foo::get() to access the singleton instance

template <typename T>
class Singleton 
{
private:
	static bool sInstanceExists;
	Singleton(Singleton const&) = delete;
	void operator=(Singleton const&) = delete;
protected:
	Singleton() 
	{
		assert(!sInstanceExists);
		sInstanceExists = true;
	}
	~Singleton() 
	{
		assert(sInstanceExists);
		sInstanceExists = false;
	}
public:
	static T &get() 
	{
		static T instance; // instance is initialised when get() is first called
		return instance;
	}
};

template<typename T>
bool Singleton<T>::sInstanceExists = false;
