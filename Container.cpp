#include "Container.h"
#include "Object.h"
#include "Player.h"

#include <iostream>

Container::Container(std::string name, std::string description) : Object::Object(name, description)
{
}

void Container::addItemToContainer(Object* item)
{
	items.push_back(item);
}

void Container::examine()
{
	inputOutputManager.printSpacer();
	inputOutputManager.printLine(7, 0, name);
	inputOutputManager.printSpacer();
	inputOutputManager.printLine(8, 0, description);
	inputOutputManager.printSpacer();
}

void Container::openContainer(Player* player)
{
	inputOutputManager.printSpacer();
	for (auto item : items)
	{
		inputOutputManager.printLine(6, 0, item->getObjectName());
	}
	inputOutputManager.printSpacer();

	if (player != NULL) //ensures player reference been taken
	{
		//transfers over all items that are in the container to the player and then removes container
		for (auto item : items)
		{
			player->takeObject(item); //gives player an item
		}
		player->dropObject(this); //dereference this container item from player's inventory
		delete this; //deletes this container
	}
}

Container::~Container()
{
}
