#include "Object.h"

#include <iostream>

Object::Object(std::string name, std::string description)
{
	this->name = name;
	this->description = description;
}

std::string Object::getObjectName()
{
	return name;
}

Object::~Object()
{
}
