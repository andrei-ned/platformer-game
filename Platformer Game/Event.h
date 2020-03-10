#pragma once
#include "EventFunction.h"
#include <forward_list>

template <class... Args>
class Event
{
public:
	Event() {};
	~Event() {};
	void invoke(Args... args)
	{
		//for (unsigned int i = 0; i < mFunctions.size(); i++)
		//{
		//	mFunctions.at(i)(&args...);
		//}
		for (auto& func : mFunctions)
			func.invoke(&args...);
	}
	void operator += (EventFunction<Args...> function)
	{
		mFunctions.push_front(function);
	}
	void operator -= (EventFunction<Args...> function)
	{
		mFunctions.remove(function);
	}
private:
	//std::vector<std::function<void(Args...)>> mFunctions;
	std::forward_list<EventFunction<Args...>> mFunctions;
};
