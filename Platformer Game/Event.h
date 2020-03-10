#pragma once
#include <functional>

template <class... Args>
class Event
{
public:
	Event() {};
	~Event() {};
	void invoke(Args... args)
	{
		for (unsigned int i = 0; i < mFunctions.size(); i++)
		{
			mFunctions.at(i)(&args...);
		}
	}
	void add(std::function<void(Args...)> function)
	{
		mFunctions.push_back(function);
	}
private:
	std::vector<std::function<void(Args...)>> mFunctions;
};
