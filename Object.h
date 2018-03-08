#pragma once
#include <string>

class Object
{
protected:
	std::string name; //objects name
	std::string description; //objects description

public:
	Object(std::string name, std::string description);

	virtual void examine() = 0; //used by child classes to describe item

	//get
	std::string getObjectName(); //returns object name

	~Object();
};

