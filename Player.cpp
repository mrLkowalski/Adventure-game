#include "Player.h"
#include "Object.h"
#include "AdventureRoom.h"
#include "Container.h"

#include <iostream>
#include <algorithm>

Player::Player()
{
}

void Player::takeObject(Object* object)
{
	if (object != 0)
	{
		inventory.push_back(object);

		inputOutputManager.printSpacer();
		inputOutputManager.printLine(2, 0,"You have picked up an item");
		inputOutputManager.printSpacer();
	}
	else
	{
		inputOutputManager.printSpacer();
		inputOutputManager.printLine(4, 0, "You have entered wrong item name");
		inputOutputManager.printSpacer();
	}
}

void Player::dropObject(Object* object)
{
	for (auto objectFor : inventory)
	{
		if (objectFor == object)
		{
			inventory.remove(object);

			inputOutputManager.printSpacer();
			inputOutputManager.printLine(2, 0, "You have dropped an item");
			inputOutputManager.printSpacer();

			break;
		}
	}
}

void Player::examineObject(Object* object)
{
	if (object != NULL)
	{
		if (typeid(*object) == typeid(Container))
		{
			object->examine();
			Container* tempContainerPtr = dynamic_cast<Container*>(object);
			tempContainerPtr->openContainer(this);
		}
		else
		{
			object->examine();
		}
	}
	else
	{
		inputOutputManager.printSpacer();
		inputOutputManager.printLine(4, 0, "You have entered wrong item's name");
		inputOutputManager.printSpacer();
	}
}

void Player::showInventory()
{
	inputOutputManager.printSpacer();

	for (auto& object : inventory) //iterates through the player's inventory and lists items
	{
		inputOutputManager.printLine(6, 0, object->getObjectName());
	}

	inputOutputManager.printSpacer();
}


void Player::setAdventureRoom(AdventureRoom* currentAdventureRoom)
{
	this->currentAdventureRoom = currentAdventureRoom;
}

AdventureRoom* Player::getAdventureRoom()
{
	return currentAdventureRoom;
}

std::list<Object*>* Player::getInventory()
{
	return &inventory;
}

Object* Player::getObject(std::string objectName)
{
	std::transform(objectName.begin(), objectName.end(), objectName.begin(), ::tolower); //converts input to lower case

	for (auto& object : inventory)
	{
		std::string tempObjectName = object->getObjectName();
		std::transform(tempObjectName.begin(), tempObjectName.end(), tempObjectName.begin(), ::tolower); //converts input to lower case

		if (tempObjectName == objectName)
		{
			return object;
		}
	}
	return 0;
}


Player::~Player()
{
}
