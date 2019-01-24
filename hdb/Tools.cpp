/*
 * Tools.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: marchi
 */

#include "Tools.h"
#include <string>
#include <regex>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>

const std::regex RESNAME{R"(^.*\[ *([A-Z][A-Z0-9]*) *\].*)"};
const std::regex ATOMS{R"(^.*\[ *(atoms) *\].*)"};
const std::regex BONDS{R"(^.*\[ *(bonds) *\].*)"};
const std::regex IMPR{R"(^.*\[ *(imp.*) *\].*)"};
const std::regex CMAP{R"(^.*\[ *(cmap) *\].*)"};
const std::regex BONDED{R"(^.*\[ *(bonded.*) *\].*)"};
using std::string;
using std::vector;
using std::map;
void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);

	// Repeat till end is reached
	while( pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos =data.find(toSearch, pos + replaceStr.size());
	}
}

std::vector<std::string> split(const std::string& s, string del)
{
	const string ranstr{"$3EA"};
	string temp{s};
	if(del.find_first_not_of('\t') != std::string::npos) findAndReplaceAll(temp,"\t"," ");

	if(del.find_first_not_of(' ') != std::string::npos){
		findAndReplaceAll(temp," ",ranstr);
		findAndReplaceAll(temp,del," ");
	}

	std::istringstream iss(temp);
	std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
	                                 std::istream_iterator<std::string>());
	if(del.find_first_not_of(' ') != std::string::npos){
		for(auto & o: tokens){
			findAndReplaceAll(o,ranstr," ");
		}
	}
   return tokens;
}
void eraseBlanks(string & str){
	str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x){return std::isspace(x);}), str.end());
}

vector<string> mySplit(string sstr){
	vector<string> out;
	vector<string> strs=split(sstr,"\n");
	map<string,vector<string>> residues;
	string name;

	for(size_t o{0};o<strs.size();o++){
		vector<string> st0=split(strs[o],";");
		if(st0.size() == 0 ) continue;
		if(st0[0].find_first_not_of(' ') == std::string::npos) continue;
		std::cmatch m,mb;
		std::regex_match(st0[0].c_str(),m,RESNAME);
		std::regex_match(st0[0].c_str(),mb,BONDED);

		if(m.size() == 2){
			name=m[1];
			residues[name].push_back(st0[0]);
		}else if(mb.size() == 2){
			name=mb[1];
			residues[name]=vector<string>();
		}else{
			residues[name].push_back(st0[0]);
		}
	}
	for(auto it0=residues.begin();it0!= residues.end();it0++){
		string str{""};

		for(auto it1: it0->second){
			str+=it1+"\n";
		}
		out.push_back(str);
	}
	return out;
}



