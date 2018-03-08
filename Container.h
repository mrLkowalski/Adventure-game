#pragma once
#include "Object.h"
#include "Player.h"
#include "InputOutputManager.h"

#include <list>

class Container :
	public Object
{
	InputOutputManager inputOutputManager; //instance used for input and output

	std::list<Object*> items; //stores contained items
public:
	Container(std::string name, std::string description);

	void addItemToContainer(Object* item); //adds item to the list of contained items

	void examine(); //prints out name and description
	void openContainer(Player* player); //returns items contained to the player and destroys self

	~Container();
};