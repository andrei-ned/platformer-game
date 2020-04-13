#pragma once
#include "EventFunction.h"
#include <forward_list>


// Holds EventFunctions to be invoked when something happens (e.g. a UI button is clicked)
template <typename... Args>
class Event
{
public:
	Event() {};
	~Event() {};

	void invoke(Args... args)
	{
		for (auto& func : mFunctions)
			func.invoke(args...);
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
	std::forward_list<EventFunction<Args...>> mFunctions;
};
