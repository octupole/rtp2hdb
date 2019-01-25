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
using std::cout;
using std::endl;
class MyToken{
	vector<string> vec;
	vector<string> label;
public:
	MyToken();
	MyToken(string y,regex sep);
	string GetLabel(int i){return label.at(i);};
	size_t size(){return vec.size();}
	string & operator[](size_t o){return vec[o];}
	virtual ~MyToken();
};

#endif /* MYTOKEN_H_ */
