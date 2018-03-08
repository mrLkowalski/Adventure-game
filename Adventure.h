#pragma once
#include "AdventureRoom.h"
#include "Player.h"
#include "InputOutputManager.h"

#include <list>
#include <vector>

class Adventure
{
	InputOutputManager inputOutputManager; //instance used for input and output

	bool exit = false; //bool used to terminate game

	//game instances
	std::list<AdventureRoom> adventureRooms; //list that contains of adventure rooms
	Player player; //creates instance of the player

	//main methods
	void loadAdventureRooms();
	void refreshGameSequence();

	//input methods
	std::string playerInput();
	bool isInputMovement(std::string input);
	void performPlayerMovement(std::string input);
	bool isForcedMovement();
	void performPlayerForcedMovement();
	bool isInputCommand(std::string input);
	void performCommand(std::string input);
	void checkForEndGame();

	//input commands
	const std::string TAKE = "take";
	const std::string DROP = "drop";
	const std::string EXAMINE = "examine";
	const std::string INVENTORY = "inventory";
	const std::string LOOK = "look";
	const std::string HELP = "help";
	const std::string EXIT = "exitgame";

	void helpInstructions(); //prints out instructions

public:
	Adventure();

	void run(); //runs game

	~Adventure();
};

