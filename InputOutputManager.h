#pragma once
#include <string>



class InputOutputManager
{

public:
	InputOutputManager();

	std::string inputLine(int textColour, int backColour); //asks for input in chosen colour
	void printSpacer(); //prints empty text line
	void printLine(int textColour, int backColour, std::string textLine); //prints text line in chosen colour then switches back colour to default

	~InputOutputManager();
};

