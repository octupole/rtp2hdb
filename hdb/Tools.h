/*
 * constants.h
 *
 *  Created on: Jan 22, 2019
 *      Author: marchi
 */

#ifndef HDB_TOOLS_H_
#define HDB_TOOLS_H_
#include <string>
#include <vector>

using std::string;
using std::vector;

void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr);

std::vector<std::string> split(const std::string& s, string del=" ");
void eraseBlanks(string & str);

vector<string> mySplit(string sstr);
#endif /* HDB_TOOLS_H_ */
