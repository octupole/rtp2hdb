/*
 * MyToken.cpp
 *
 *  Created on: Feb 11, 2012
 *      Author: marchi
 */

#include "MyToken.h"

MyToken::MyToken() {
	// TODO Auto-generated constructor stub

}
MyToken::MyToken(string y,regex re){
	std::string::const_iterator start, end, startp;
	start = y.begin();
	end = y.end();
	boost::match_results<std::string::const_iterator> what,what1;
	boost::match_flag_type flags = boost::match_default;
	int count=0;
	while(regex_search(start, end, what, re, flags))
	{
		// what[0] contains the whole string
		string labs(what[1].first,what[1].second);
		label.push_back(labs);

		if(count++){
			string tmp(start,what[0].first);
			vec.push_back(tmp);
		}
		start = what[0].second;
		// update flags:
		flags |= boost::match_prev_avail;
		flags |= boost::match_not_bob;
	}
	string tmp(start,end);
	vec.push_back(tmp);
	try{
		if(vec.size() != label.size()) throw "Why the numbers of substrings and tokens are not identical?";

	}
	catch(const char * s){
		std::cout << s << "\n";
		exit(1);
	}
}

MyToken::~MyToken() {
	vec.clear();
	label.clear();
	// TODO Auto-generated destructor stub
}

