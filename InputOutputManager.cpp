#include "InputOutputManager.h"
#include <iostream>
#include <Windows.h>
#include <iostream>

#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)
enum
	concol  // enumeration type
{
	black = 0,
	dark_blue = 1,
	dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5,
	dark_pink = 5,
	dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11,
	cyan = 11,
	red = 12,
	purple = 13,
	pink = 13,
	magenta = 13,
	yellow = 14,
	white = 15
};

InputOutputManager::InputOutputManager()
{
}

void setColor(int textcol, int backcol)
{
	unsigned short wAttributes = (backcol << 4) | textcol;
	SetConsoleTextAttribute(std_con_out, wAttributes);
}

std::string InputOutputManager::inputLine(int textColour, int backColour)
{
	setColor(textColour, backColour);

	std::string input;
	std::getline(std::cin, input);

	setColor(7, 0);

	return input;
}

void InputOutputManager::printLine(int textColour, int backColour, std::string textLine)
{
	setColor(textColour, backColour);

	std::cout << textLine << std::endl;

	setColor(7, 0);
}

void InputOutputManager::printSpacer()
{
	std::cout << std::endl;
}

InputOutputManager::~InputOutputManager()
{
}
