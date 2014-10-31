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
	std::cout << "Name: " << GetValueToString("Name","GBPTNK") << std::endl;
	std::cout << "Prerequisite: " << GetValueToCStr("Prerequisite","GBPTNK") << "\n";
	std::cout << "Cost: " << GetValueToInt("Cost","GBPTNK") << '\n';
	CleanUpIniMemory();
	return 0;
}
