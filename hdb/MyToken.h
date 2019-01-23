/*
 * MyToken.h
 *
 *  Created on: Feb 11, 2012
 *      Author: marchi
 */

#ifndef MYTOKEN_H_
#define MYTOKEN_H_
#include <boost/regex.hpp>
#include <string>
#include <vector>
#include <iostream>
using namespace boost;

using  std::string;
using std::vector;

class MyToken: public vector<string> {
	vector<string> label;
public:
	MyToken();
	MyToken(string y,regex sep);
	string GetLabel(int i){return label.at(i);};
	virtual ~MyToken();
};

#endif /* MYTOKEN_H_ */
