
#pragma once
#include <string>

class Observer{
public:

	virtual ~Observer() = default;
	virtual void Execute(const std::string& event_name) const = 0;
};


 