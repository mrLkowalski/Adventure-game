#pragma once
#include <map>
#include <string>

class MotionTable
{
	std::map<std::pair<std::string, int>, std::string> exitsMap; //map that stores room name, room number and object's name needed to access exit
public:
	MotionTable();

	void addExit(std::string direction, int roomNumber, std::string objectName = ""); //adds exit to motion table

	//get
	std::map<std::pair<std::string, int>, std::string>* getExitsMap(); //returns exits map
	~MotionTable();
};

