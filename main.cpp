/**
 * File:	Main.cpp
 * Author:	LonelyDrifter
 *
 * Created on	October, 18, 2014, 01:23 AM
 */

/**
 * include headers
 *
 */
 #include "iniParser.h"
 #include <iostream>
int main(int argc, char *argv[], char *envp[])
{
	ParserIniFile("test.ini");
	std::cout << "Name: " << GetValueToString("Name") << std::endl;
	std::cout << "Strength: " << GetValueToInt("Strength") << "\n";
	std::cout << "Cost: " << GetValueToCStr("Cost") << "\n";
	CleaningUpIniMemory();
	return 0;
}
