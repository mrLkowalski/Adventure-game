#include "Key.h"

#include <string>
#include <iostream>

Key::Key(std::string name, std::string description) : Object::Object(name, description)
{
}

void Key::examine()
{
	inputOutputManager.printSpacer();
	inputOutputManager.printLine(7, 0, name);
	inputOutputManager.printSpacer();
	inputOutputManager.printLine(8, 0, description);
	inputOutputManager.printSpacer();
}

Key::~Key()
{
}
