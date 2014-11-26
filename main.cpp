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

#ifdef DEBUG
#endif
int main(int argc, char *argv[], char *envp[])
{
	ParseIniFile("rulesmd.ini");
	//===================DEBUG====================
#ifdef DEBUG
	std::string str;
	str = GetValueToString("Prerequisite", "GBPTNK");
	std::cout << str.c_str() << std::endl;
	std::cout << "==============" << std::endl;
	std::cout << GetValueToCStr("Name", "General") << std::endl;
	//std::cout << "==============" << std::endl;
	//std::cout << GetValueToString("Prerequisite", "GBPTNK").c_str() << std::endl;
#endif
	//=================== END ====================
#ifndef DEBUG
	std::cout << GetValueToString("UIName", "GBPTNK") << std::endl;
	std::cout << GetValueToCStr("Prerequisite","GBPTNK") << std::endl;
	std::cout << GetValueToInt("Cost", "GBPTNK") << std::endl;
#endif
	CleanUpIniMemory();
	return 0;
}
