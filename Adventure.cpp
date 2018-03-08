#include "Adventure.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <experimental\filesystem>

Adventure::Adventure()
{
}

void Adventure::run()
{
	loadAdventureRooms(); //loads all adventureRooms from files

	player.setAdventureRoom(&adventureRooms.front()); //assigns first room to the player

	inputOutputManager.printSpacer();
	inputOutputManager.printLine(12, 14, "-----------------------------START GAME-----------------------------");
	inputOutputManager.printSpacer();

	while (!exit) //while false run the game
	{
		refreshGameSequence();
	}
}

void Adventure::loadAdventureRooms()
{
	std::string adventureRoomsFolder = "adventureRooms\\"; //start off directory
	for (auto & adventureRoomPath : std::experimental::filesystem::directory_iterator(adventureRoomsFolder)) //runs for loop using directory iterator to read out name of files
	{
		std::cout << adventureRoomPath.path().string() << std::endl;
		adventureRooms.push_back(AdventureRoom(adventureRoomPath.path().string())); //creates new instance of adventureRoom and passes over file path to its parameter
	}
}

void Adventure::refreshGameSequence()
{
	if (isForcedMovement())
	{
		player.getAdventureRoom()->showRoom(false);
		performPlayerForcedMovement();
	}

	bool knownCommand = false;
	std::string input;
	input = playerInput();

	if (isInputMovement(input))
	{
		performPlayerMovement(input);
		knownCommand = true;
	}

	if (isInputCommand(input))
	{
		performCommand(input);
		knownCommand = true;
	}

	if (!knownCommand)
	{
		inputOutputManager.printSpacer();
		inputOutputManager.printLine(15, 5, "You entered unknown command, type in help to get list of commands or look to get list of movement directions");
		inputOutputManager.printSpacer();
	}

	checkForEndGame();
}

std::string Adventure::playerInput()
{
	inputOutputManager.printSpacer();
	inputOutputManager.printLine(12, 14, "user input");
	inputOutputManager.printSpacer();

	return inputOutputManager.inputLine(0,15);
}

bool Adventure::isInputMovement(std::string input)
{
	std::string keyword;
	for (const auto pair : *player.getAdventureRoom()->getMotionTable()->getExitsMap())
	{

		//converts both input and a keyword to lowercase to preserve consistency
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		keyword = pair.first.first;
		std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

		if (input == keyword) //compares input with the keyword
		{
			return true;
		}
	}
	return false;
}

void Adventure::performPlayerMovement(std::string input)
{
	std::string keyword;
	for (const auto pair : *player.getAdventureRoom()->getMotionTable()->getExitsMap())
	{

		//converts both input and a keyword to lowercase to preserve consistency
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		keyword = pair.first.first;
		std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

		if (input == keyword) //compares input with the keyword
		{
			for (auto& room : adventureRooms)
			{
				if (room.getNumber() == pair.first.second)
				{
					if (pair.second == "")
					{
						player.setAdventureRoom(&room); //moves player to the room
						player.getAdventureRoom()->roomVisited(); //flags room as visited
						break;
					}
					else
					{
						bool playerHasItemRequired = false; //flag that determins whether player has item to proceed to a location

						for (auto& object : *player.getInventory())
						{
							std::string playerItem = object->getObjectName();
							std::string itemRequired = pair.second;

							//converts strings that will be compared to lowercase for consistency
							std::transform(playerItem.begin(), playerItem.end(), playerItem.begin(), ::tolower);
							std::transform(itemRequired.begin(), itemRequired.end(), itemRequired.begin(), ::tolower);

							if (itemRequired == playerItem)
							{
								player.setAdventureRoom(&room); //moves player to the room
								player.getAdventureRoom()->roomVisited(); //flags room as visited
								playerHasItemRequired = true;

								inputOutputManager.printSpacer();
								inputOutputManager.printLine(2, 0, "You have successfully used item to proceed to a location");
								inputOutputManager.printSpacer();

								break;
							}
						}

						if (!playerHasItemRequired) //informs player that doesnt have item required to proceed to a location
						{
							inputOutputManager.printSpacer();
							inputOutputManager.printLine(4, 0, "You do not have required item to be able to proceed to the location");
							inputOutputManager.printSpacer();
						}
					}
				}
			}
			break;
		}
	}
}

bool Adventure::isForcedMovement()
{
	std::string keyword;
	for (const auto pair : *player.getAdventureRoom()->getMotionTable()->getExitsMap()) //tests exits for forced movement
	{
		//converts keyword to lower case to compare with the checked word successfully
		keyword = pair.first.first;
		std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

		if (keyword == "forced")
		{
			return true;
		}
	}
	return false;
}

void Adventure::performPlayerForcedMovement()
{
	std::string keyword;

	for (const auto pair : *player.getAdventureRoom()->getMotionTable()->getExitsMap()) //tests exits for forced movement
	{
		//converts keyword to lower case to compare with the checked word successfully
		keyword = pair.first.first;
		std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

		if (keyword == "forced")
		{
			for (auto& room : adventureRooms)
			{
				if (room.getNumber() == pair.first.second)
				{
					player.setAdventureRoom(&room); //moves player to the room
					player.getAdventureRoom()->roomVisited(); //flags room as visited
					break;
				}
			}
		}
	}
}

bool Adventure::isInputCommand(std::string input)
{
	std::transform(input.begin(), input.end(), input.begin(), ::tolower); //converts input to lower case

	if (input.find(" "))
	{
		int pos = input.find(" "); //saves the position of the slash
		input = input.substr(0, pos); //seperates string onto the first part which is a room number
	}


	if (input == TAKE || input == DROP || input == EXAMINE || input == INVENTORY || input == LOOK || input == HELP || input == EXIT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Adventure::performCommand(std::string input)
{
	std::string objectName = "";

	std::transform(input.begin(), input.end(), input.begin(), ::tolower); //converts input to lower case

	if (input.find(" "))
	{
		int pos = input.find(" ");
		objectName = input.substr(pos + 1);
		input = input.substr(0, pos);
	}

	if (input == TAKE)
	{
		player.takeObject(player.getAdventureRoom()->getObject(objectName)); //player takes an item
		player.getAdventureRoom()->removeObject(player.getAdventureRoom()->getObject(objectName)); //item is removed from a room's items list
	}
	else if (input == DROP)
	{
		player.getAdventureRoom()->addObject(player.getObject(objectName)); //player dropes an item
		player.dropObject(player.getObject(objectName)); //item is added to a room's items list

	}
	else if (input == EXAMINE)
	{
		player.examineObject(player.getObject(objectName)); //player examins item
	}
	else if (input == INVENTORY)
	{
		player.showInventory(); //player display inventory
	}
	else if (input == LOOK)
	{
		player.getAdventureRoom()->showRoom(); //player display room info
	}
	else if (input == HELP)
	{
		helpInstructions(); //display game instructions
	}
	else if (input == EXIT)
	{
		exit = true; //end game
	}
}

void Adventure::helpInstructions()
{

	inputOutputManager.printSpacer();
	inputOutputManager.printLine(15, 5, "Possible commands:");
	inputOutputManager.printSpacer();
	inputOutputManager.printLine(15, 5, "look - to examin a room, for exits");
	inputOutputManager.printLine(15, 5, "take \"item name\" - to take an item");
	inputOutputManager.printLine(15, 5, "drop \"item name\"- to drop an item");
	inputOutputManager.printLine(15, 5, "examine \"item name\" - to examine an item");
	inputOutputManager.printLine(15, 5, "inventory - to display player's inventory");
	inputOutputManager.printLine(15, 5, "exitgame - to exit game");
	inputOutputManager.printSpacer();
}

void Adventure::checkForEndGame()
{
	if (player.getAdventureRoom()->getNumber() == 11)
	{
		player.getAdventureRoom()->showRoom(); //player display room info

		inputOutputManager.printSpacer();
		inputOutputManager.printLine(12, 14, "-----------------------------THE END-----------------------------");
		inputOutputManager.printSpacer();

		system("pause");
	}
}

Adventure::~Adventure()
{
}