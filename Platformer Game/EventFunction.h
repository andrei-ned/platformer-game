#pragma once
#include <functional>


// Wrapper for an std::function with a unique id
template <class... Args>
class EventFunction
{
public:
	EventFunction(std::function<void(Args...)> func) : mFunction(func) { mId = sCount++; }
	bool operator==(const EventFunction& other) { return getId() == other.getId(); }
	int getId() const { return mId; }
	void invoke(Args... args) { mFunction(args...); }
private:
	std::function<void(Args...)> mFunction;
	int mId;
	int sCount = 0;
};

