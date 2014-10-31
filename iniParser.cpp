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
#include <vector>

/**
 * global section
 *
 */
typedef struct _line{
	std::string key;
	std::string value;
	std::string comment;
	std::string head;
}LINE, *PLINE;

std::vector<PLINE> gIniMemory_Section_Head;
std::vector<std::vector<PLINE>> gIniMemory;

int ParseIniFile(std::string iniFile)
{
	//Open a filestream;
	std::ifstream ifs(iniFile);
	if (!ifs.is_open())
		return 0;
	//Read a line from stream;
	std::string iniFile_Line;
	//Save a line in memory as local
	PLINE iniMemory_Line = new LINE;
	//Save the current section index for oprating the lines belonged to it
	std::vector<std::vector<PLINE>>::size_type sectionPos = std::string::npos;
	
	std::vector<PLINE> vec;
	vec.push_back(nullptr);

	gIniMemory_Section_Head.push_back(nullptr);
	gIniMemory_Section_Head.back() = new LINE;
	(gIniMemory_Section_Head.back())->head = "Default";
	gIniMemory.push_back(vec);

	while (!ifs.eof())
	{
		std::getline(ifs,iniFile_Line);
		
		//trim spaces;
		Trim(iniFile_Line);

		if (iniFile_Line.empty())
			continue;
		//=========parse and trim comments==============
		//support ';' comment whatever it is at;
		if (iniFile_Line.find(';') != std::string::npos)
		{
			iniMemory_Line->comment = iniFile_Line.substr(iniFile_Line.find(';')+1);
			iniFile_Line.pop_back();
		}
		//==================end=========================
		
		//trim spaces;
		Trim(iniFile_Line);

		//=========deal with section head===========
		if (iniFile_Line.front() == '[' && iniFile_Line.back() == ']')
		{
			iniMemory_Line->head = iniFile_Line.substr(1,iniFile_Line.size()-2);
			gIniMemory_Section_Head.push_back(nullptr);
			gIniMemory_Section_Head.back() = new LINE;
			(gIniMemory_Section_Head.back())->head = iniMemory_Line->head;
			(gIniMemory_Section_Head.back())->comment = iniMemory_Line->comment;
			gIniMemory.push_back(vec);
			continue;
		}
		//================== end ===================

		//deal with lines;
		iniMemory_Line->key = GetKeyFromLine(iniFile_Line);
		iniMemory_Line->value = GetValueFromLine(iniFile_Line);
		(gIniMemory.back()).back() = new LINE;
		((gIniMemory.back()).back())->key = iniMemory_Line->key;
		((gIniMemory.back()).back())->value = iniMemory_Line->value;
		((gIniMemory.back()).back())->comment = iniMemory_Line->comment;
		((gIniMemory.back()).back())->head = iniMemory_Line->head;
	}
	ifs.close();
	return 1;
}

void CleanUpIniMemory()
{
	while (gIniMemory_Section_Head.empty())
	{
		delete gIniMemory_Section_Head.back();
		gIniMemory_Section_Head.pop_back();
	}
	while (gIniMemory.empty())
	{
		while ((gIniMemory.back()).empty())
		{
			delete (gIniMemory.back()).back();
			(gIniMemory.back()).pop_back();
		}
		gIniMemory.pop_back();
	}
}

std::string GetValueToString(std::string key, std::string section_Head)
{
	std::vector<PLINE>::size_type section_Total = gIniMemory_Section_Head.size();
	std::vector<PLINE>::size_type section_Lines_Total = 0;
	for (decltype(section_Total) i = 0; i < section_Total; ++i)
	{
		if (gIniMemory_Section_Head[i]->head == section_Head)
		{
			section_Lines_Total = gIniMemory[i].size();
			for (decltype(section_Lines_Total) j = 0; j < section_Lines_Total; ++j)
			{
				if (gIniMemory[i][j]->key == key)
					return gIniMemory[i][j]->value;
			}
		}
	}
	return "";
}

const char *GetValueToCStr(std::string key, std::string section_Head)
{
	return (GetValueToString(key,section_Head)).c_str();
}

int GetValueToInt(std::string key, std::string section_Head)
{
	return std::stoi((GetValueToString(key,section_Head)));
}

std::string GetKeyFromLine(std::string line)
{
	std::string::size_type found = line.find('=');
	if (found == std::string::npos || found > 100)
		return "";
	return Trim(line.substr(0,found));
}

std::string GetValueFromLine(std::string line)
{
	std::string::size_type found = line.find('=');
	if (found == std::string::npos || found > 100)
		return "";
	return Trim(line.substr(found+1));
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
