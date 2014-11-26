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
#include <unordered_map>
#include <utility>

/**
 * global section
 *
 */
#define LINETYPE_UNSUPPORT (0x00000000);
#define LINETYPE_SECTION_HEAD (0x00000001);
#define LINETYPE_COMMENT (0x00000002);
#define LINETYPE_COMMON (0x00000004);

typedef struct _line{
	unsigned int lineType;
	std::string key;
	std::string value;
	std::string comment;
	std::string head;
}LINE, *PLINE;

std::unordered_map<std::string, std::vector<LINE>> gIniMemory;

int ParseIniFile(std::string iniFile)
{
	//Open a filestream;
	std::ifstream ifs(iniFile);
	if (!ifs.is_open())
		return 0;
	//Read a line from stream;
	std::string iniFile_Line;
	//Save a line in memory as local
	LINE iniMemory_Line = {0,"","","",""};
	
	while (!ifs.eof())
	{
		std::getline(ifs,iniFile_Line);
		
		//trim spaces;
		iniFile_Line = Trim(iniFile_Line);

		if (iniFile_Line.empty())
			continue;
		//=========parse and trim comments==============
		//support ';' comment whatever it is at;
		if (iniFile_Line.find(';') != std::string::npos)
		{
			iniMemory_Line.lineType |= LINETYPE_COMMENT;
			iniMemory_Line.comment = iniFile_Line.substr(iniFile_Line.find(';')+1);
			iniFile_Line = iniFile_Line.substr(0,iniFile_Line.find(';'));
		}
		//==================end=========================
		
		//trim spaces;
		iniFile_Line = Trim(iniFile_Line);

		//=========deal with section head===========
		if (iniFile_Line.front() == '[' && iniFile_Line.back() == ']')
		{
			iniMemory_Line.lineType |= LINETYPE_SECTION_HEAD;
			iniMemory_Line.head = iniFile_Line.substr(1,iniFile_Line.size()-2);
			std::vector<LINE> vec;
			gIniMemory.insert(std::make_pair(iniMemory_Line.head,vec));

			//clear up iniMemory_Line struct;
			iniMemory_Line.lineType = LINETYPE_UNSUPPORT;
			iniMemory_Line.key = "";
			iniMemory_Line.value = "";
			iniMemory_Line.comment = "";
			continue;
		}
		//================== end ===================

		//deal with lines;
		iniMemory_Line.key = GetKeyFromLine(iniFile_Line);
		iniMemory_Line.value = GetValueFromLine(iniFile_Line);
		if (!((iniMemory_Line.key).empty()) && !((iniMemory_Line.value).empty()))
			iniMemory_Line.lineType |= LINETYPE_COMMON;
		if (iniMemory_Line.lineType)
		{
			auto found = gIniMemory.find(iniMemory_Line.head);
			if (found == gIniMemory.end())
				continue;
			(found->second).push_back(iniMemory_Line);
			iniMemory_Line.lineType = LINETYPE_UNSUPPORT;
			iniMemory_Line.key = "";
			iniMemory_Line.value = "";
			iniMemory_Line.comment = "";
		}
	}
	ifs.close();

	return 1;
}

void CleanUpIniMemory()
{
	while (!gIniMemory.empty())
		gIniMemory.clear();

}

std::string GetValueToString(std::string key, std::string head)
{
	auto found = gIniMemory.find(head);
	if (found != gIniMemory.end())
	{
		for (auto beg = (found->second).begin(),end = (found->second).end(); beg != end; ++beg)
		{
			if (beg->key == key)
				return beg->value;
		}
	}
	return "";
}

const char *GetValueToCStr(std::string key, std::string head)
{
	auto found = gIniMemory.find(head);
	if (found != gIniMemory.end())
	{
		for (auto beg = (found->second).begin(),end = (found->second).end(); beg != end; ++beg)
		{
			if (beg->key == key)
				return (beg->value).c_str();
		}
	}
	return "";
}

int GetValueToInt(std::string key, std::string head)
{
	auto found = gIniMemory.find(head);
	if (found != gIniMemory.end())
	{
		for (auto beg = (found->second).begin(),end = (found->second).end(); beg != end; ++beg)
		{
			if (beg->key == key)
				return std::stoi(beg->value);
		}
	}
	return 0;
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
