/**
 * File:	iniParser.cpp
 * Author:	LonelyDrifter
 *
 * Created:	October 11, 2014, 01:46 AM
 */

/**
 * include headers
 *
 */
#include "iniParser.h"
#include <fstream>

/**
 * global section
 *
 */
typedef struct _line{
	std::string key;
	std::string value;
}LINE, *PLINE;

unsigned int i = 0; //NumofLine
PLINE IniFile_Table[1024] = {0};

int ParseIniFile(std::string iniFile)
{
	//Open a filestream;
	std::ifstream ifs(iniFile);
	if (!ifs.is_open())
		return 0;
	//Read a line from stream;
	std::string Line;
	while (!ifs.eof())
	{
		std::getline(ifs,Line);
		if (Line.empty() || Line.substr(0,1) == "#")
			continue;
		std::string Key;
		Key = GetKeyFromLine(Line);
		if (Key.empty())
			continue;
		IniFile_Table[i] = new LINE;
		IniFile_Table[i]->key = Key;
		IniFile_Table[i]->value = GetValueFromLine(Line);
		++i;
	}
	// --i;
	ifs.close();
	return 1;
}

void CleanUpIniMemory()
{
	for (int j = 0; j < i; ++j)
		delete IniFile_Table[j];
	i = 0;
}

std::string GetValueToString(std::string key)
{
	for (int j = 0; j < i; ++j)
		if (IniFile_Table[j]->key == key)
			return IniFile_Table[j]->value;
	return "";
}

const char *GetValueToCStr(std::string key)
{
	for (int j = 0; j < i; ++j)
		if (IniFile_Table[j]->key == key)
			return IniFile_Table[j]->value.c_str();
	return "";
}

int GetValueToInt(std::string key)
{
	for (int j = 0; j < i; ++j)
		if (IniFile_Table[j]->key == key)
			return stoi(IniFile_Table[j]->value);
	return 0;
}

std::string GetKeyFromLine(std::string Line)
{
	std::string::size_type found = Line.find('=');
	if (found == std::string::npos || found > 100)
		return "";
	return Trim(Line.substr(0,found));
}

std::string GetValueFromLine(std::string Line)
{
	std::string::size_type found = Line.find('=');
	if (found == std::string::npos || found > 100)
		return "";
	return Trim(Line.substr(found+1));
}

std::string LTrim(std::string str)
{
	std::string::size_type found = str.find_first_not_of(' ');
	if (found == std::string::npos)
		return "";
	return str.substr(found);
}

std::string RTrim(std::string str)
{
	std::string::size_type found = str.find_last_not_of(' ');
	if (found == std::string::npos)
		return "";
	return str.substr(0, found+1);
}

std::string Trim(std::string str)
{
	return LTrim(RTrim(str));
}
