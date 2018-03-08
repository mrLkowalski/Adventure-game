#pragma once
#include "Object.h"
#include "MotionTable.h"
#include "InputOutputManager.h"

#include <string>
#include <list>

class AdventureRoom
{
	InputOutputManager inputOutputManager; //instance used for input and output

	int number = 0; //room id
	std::string name = ""; //room name
	std::list<std::string> description; //room description
	std::list<Object*> objects; //stores objects within the room
	bool visited = false;
	MotionTable motionTable; //specifies exits and where they lead

	void readRoom(std::string fileName); //method used for reading a room from a file

public:
	AdventureRoom(std::string fileName); //calls readRoom therefore need same parameter variable

	void roomVisited(); //marks room as visited
	void showRoom(bool exitsVisible = true); //prints out room info if parameter true
	void addObject(Object* object); //adds object to the room
	void removeObject(Object* object); //removes object from the room

	//get
	Object* getObject(std::string objectName); //returns object of given name
	int getNumber(); //return room number
	MotionTable* getMotionTable(); //return room motion table

	~AdventureRoom();
};