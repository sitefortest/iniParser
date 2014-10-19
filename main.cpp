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
	ParseIniFile("test.ini");
	std::cout << "Name: " << GetValueToString("Name") << std::endl;
	std::cout << "Prerequisite: " << GetValueToCStr("Prerequisite") << "\n";
	std::cout << "Cost: " << GetValueToInt("Cost") << '\n';
	CleanUpIniMemory();
	return 0;
}
