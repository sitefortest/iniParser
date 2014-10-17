#pragma once
/**
 * File:	iniParser.h
 * Author:	LonelyDrifter
 *
 * Created:	October, 11, 2014, 12:09 AM
 */

/**
 * include headers
 *
 */
#include <string>

/**
 * parse a inifile that only support '#'comment lines, "key = value" lines and null line; don't suppotr sections and others comment styles.
 *
 * @param:	name of the file to be parsed
 * @return:	the state of the result;
 */
int ParseIniFile(std::string);

/**
 * clean up the memory used to store the iniFile
 *
 * @param:	none
 * @return:	none
 */
void CleanUpIniMemory();

/**
 * get key's value and convert to std::string
 *
 * @param:	the key that is wanted to be searched
 * @return:	the std::string value of the key
 */
std::string GetValueToString(std::string);

/**
 * get key's value and convert to c_str
 *
 * @param:	the requested key
 * @return:	c_str value of the requested key
 */
const char *GetValueToCStr(std::string);

/**
 * get key's value and convert to int
 *
 * @param:	the requested key
 * @return:	int value of the requested key
 */
int GetValueToInt(std::string);

/**
 * parse a line and get the string that is in the left of the '=' character
 *
 * @param:	a line
 * @return:	a std::string object, if the line is empty or there is no '=' character, the string is empty string
 */
std::string GetKeyFromLine(std::string);

/**
 * parse a line and get the string that is in the right of the '='character
 *
 * @param:	a line
 * @return:	a std::string object, if the line is empty or there is no '=' character, the string is empty string
 */
std::string GetValueFromLine(std::string);

/**
 * trim the spaces before or behind a string
 *
 * @param:	a string
 * @return:	a string trimed
 */
std::string LTrim(std::string);
std::string RTrim(std::string);
std::string Trim(std::string);
