#include "MotionTable.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

MotionTable::MotionTable()
{
}

void MotionTable::addExit(std::string direction, int roomNumber, std::string objectName)
{
	std::pair<std::string, int> exitValues(direction, roomNumber);
	exitsMap.emplace(exitValues, objectName);
}

std::map<std::pair<std::string, int>, std::string>* MotionTable::getExitsMap()
{
	return &exitsMap;
}

MotionTable::~MotionTable()
{
}
