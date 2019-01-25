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
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/classification.hpp>


const boost::regex RESNAME{R"(\[ *([A-Z][A-Z0-9]*) *\])"};
const boost::regex BONDED{R"(^.*\[ *(bonded.*) *\].*)"};
using std::string;
using std::vector;


vector<string> mySplit(string sstr){
	vector<string> out;
	vector<string> strs;
	split(strs,sstr,boost::is_any_of("\n"), boost::token_compress_on);
	map<string,vector<string>> residues;
	string name;

	for(size_t o{0};o<strs.size();o++){
		vector<string> st0;
		split(st0,strs[o],boost::is_any_of(";"),boost::token_compress_on);
		if(st0.size() == 0 ) continue;
		if(st0[0].find_first_not_of(' ') == std::string::npos) continue;
		boost::smatch m,mb;

		if(boost::regex_search(st0[0],m,RESNAME)){
			name=m[1];
			residues[name].push_back(st0[0]);
		}else if(boost::regex_search(st0[0],mb,BONDED)){
			name="null";
			residues[name]=vector<string>();
		}else{
			residues[name].push_back(st0[0]);
		}
	}
	residues.erase("null");
	for(auto it0=residues.begin();it0!= residues.end();it0++){
		string str{""};

		for(auto it1: it0->second){
			str+=it1+"\n";
		}
		out.push_back(str);
	}
	return out;
}

#endif /* HDB_TOOLS_H_ */
