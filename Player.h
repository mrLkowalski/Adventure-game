#pragma once
#include "AdventureRoom.h"
#include "Object.h"
#include "InputOutputManager.h"

#include <list>

class Player
{
	InputOutputManager inputOutputManager; //instance used for input and output

	AdventureRoom* currentAdventureRoom = 0;
	std::list<Object*> inventory;
public:
	Player();

	void takeObject(Object* object);
	void dropObject(Object* object);
	void examineObject(Object* object);
	void showInventory();

	//set
	void setAdventureRoom(AdventureRoom* currentAdventureRoom);

	//get
	AdventureRoom* getAdventureRoom();
	std::list<Object*>* getInventory();
	Object* getObject(std::string objectName);

	~Player();
};

