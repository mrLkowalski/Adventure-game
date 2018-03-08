#include "AdventureRoom.h"
#include "Player.h"
#include "Key.h"
#include "Container.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>

AdventureRoom::AdventureRoom(std::string fileName)
{
	readRoom(fileName);
}

void AdventureRoom::readRoom(std::string fileName)
{
	std::ifstream roomTextFile;
	std::string textLine;
	int format = 0;

	roomTextFile.open(fileName);
	if (roomTextFile.is_open()) {
		while (std::getline(roomTextFile, textLine)) {
			if (textLine == "-----")
			{
				format++;
			}
			else
			{
				switch (format)
				{
				case 0:
					number = std::stoi(textLine);
					break;
				case 1:
					name = textLine;
					break;
				case 2:
					description.push_back(textLine);
					break;
				case 3:
					if (true) //content inside need to be capsulated as compiler would not accept following initializations in the switch statement direcly
					{
						int splitterPosition = textLine.find(',');
						std::string namePart = textLine.substr(0, splitterPosition);
						std::string infoPart = textLine.substr(splitterPosition + 1);

						if (infoPart.find('/') != std::string::npos)
						{
							int characterPosition = infoPart.find('/');
							int exitNumeral = std::stoi(infoPart.substr(0, characterPosition));
							std::string objectRequired = infoPart.substr(characterPosition + 1);
							motionTable.addExit(namePart, exitNumeral, objectRequired);
						}
						else
						{
							motionTable.addExit(namePart, std::stoi(infoPart));
						}
					}
					break;
				case 4:
					if (true)
					{
						std::istringstream iss(textLine);
						std::string part;
						std::vector<std::string> elements;
						bool addOnItem = false;

						while (std::getline(iss, part, '/'))
						{
							elements.push_back(part);
						}

						if (elements[0].find('^') != std::string::npos) //checks if first element has sign of addon item
						{
							elements[0].erase(0, 1); //erases marking character
							addOnItem = true; //flags that the item is addon item
						}

						std::string KEY = "key";
						std::string CONTAINER = "container";

						if (elements[0] == KEY && !addOnItem)
						{
							objects.push_back(new Key(elements[1], elements[2]));
						}
						else if (elements[0] == CONTAINER && !addOnItem)
						{
							objects.push_back(new Container(elements[1], elements[2]));
						}
						else if (elements[0] == KEY && addOnItem)
						{
							dynamic_cast<Container*>(objects.back())->addItemToContainer(new Key(elements[1], elements[2])); //casts to container child class and adds a item to its list
						}
					}
					break;
				}
			}
		}
	}
	roomTextFile.close();
}

void AdventureRoom::roomVisited()
{
	visited = true;
}

void AdventureRoom::showRoom(bool exitsVisible)
{
	std::map<std::pair<std::string, int>, std::string> *motionTableMap = motionTable.getExitsMap(); //creates temp pointer to read current room exits map
	
	inputOutputManager.printSpacer();
	inputOutputManager.printLine(7, 0, name); //prints out room's name
	inputOutputManager.printSpacer();

	for (auto descriptionTemp : description) //prints out room's description
	{
		inputOutputManager.printLine(8, 0, descriptionTemp);
	}
	if (exitsVisible) //determins whether exits should be visible or not (to be used for forced movement)
	{
		inputOutputManager.printSpacer();

		for (auto object : objects) //prints out items
		{
			inputOutputManager.printSpacer();
			inputOutputManager.printLine(6, 0, "You can see an item (" + object->getObjectName() + ")");
			inputOutputManager.printSpacer();
		}

		for (const auto pair : *motionTableMap) //prints out exits
		{
			inputOutputManager.printLine(3, 0, pair.first.first);
		}

		inputOutputManager.printSpacer();

		motionTableMap = 0; //dereferences temp pointer used in the method
	}
}

void AdventureRoom::addObject(Object* object)
{
	objects.push_back(object);
}

void AdventureRoom::removeObject(Object* object)
{
	for (auto objectFor : objects)
	{
		if (objectFor == object)
		{
			objects.remove(object);
			break;
		}
	}
}

Object* AdventureRoom::getObject(std::string objectName)
{
	std::transform(objectName.begin(), objectName.end(), objectName.begin(), ::tolower); //converts input to lower case

	for (auto& object : objects)
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

int AdventureRoom::getNumber()
{
	return number;
}

MotionTable* AdventureRoom::getMotionTable()
{
	return &motionTable;
}


AdventureRoom::~AdventureRoom()
{
}
