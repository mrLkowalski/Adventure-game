#pragma once
#include "Object.h"
#include "InputOutputManager.h"

#include <string>
class Key : public Object
{

	InputOutputManager inputOutputManager; //instance used for input and output

public:
	Key(std::string name, std::string description);

	void examine(); //prints out name and description

	~Key();
};

