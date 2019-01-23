/*
 * Residue.h
 *
 *  Created on: Feb 11, 2012
 *      Author: marchi
 */

#ifndef RESIDUE_H_
#define RESIDUE_H_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
#include <map>
#include <boost/regex.hpp>
#include "MyToken.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
using namespace std;
using namespace boost;
static char_separator<char> sep0("\n");
static regex re_sep0("\\n");
static regex re_split("[\\t\\n\\r\\s][\\t\\n\\r\\s]*");
static regex re_squares("\\[ *(\\w*) *\\]");
static regex re_atoms("\\[ *(atoms) *\\]");
static regex re_bonds("\\[ *(bonds) *\\]");
static regex re_impropers("\\[ *(impropers) *\\]");

class Connected: public vector<string>{
	void getVector(vector<string> y, string x, char what='A'){
		vector<string>::iterator itc;
		for(itc=y.begin();itc<y.end();++itc)
			if(*itc->begin() != what)
				if(itc->compare(x) != 0) this->push_back(*itc);
	}
public:
	Connected(){};
	Connected(vector<string> y, string x, char what='A'){getVector(y,x,what);}
	Connected & operator()(vector<string> y, string x, char what='A'){getVector(y,x,what);return *this;}
	~Connected(){this->clear();};
};
class MyHDB{
	int nr;
	int ntype;
	vector<string> series;
public:
	MyHDB():nr(0),ntype(0) {};
	MyHDB(int nnr, int nntype, vector<string>  & ss):nr(nnr),ntype(nntype),series(ss) {};
	~MyHDB(){series.clear();};
	friend std::ofstream & operator<<(std::ofstream & out, MyHDB & y){
		out << right << fixed << y.nr << "\t" << y.ntype ;
		for(unsigned int i=0; i<y.series.size();i++) out << right << fixed << "\t" << y.series[i];
		out << "\n";
		return out;
	}
	friend std::ostream & operator<<(std::ostream & out, MyHDB & y){
		out << right << fixed << y.nr << "\t" << y.ntype ;
		for(unsigned int i=0; i<y.series.size();i++) out << right << fixed << "\t" << y.series[i];
		out << "\n";
		return out;
	}
};
class Residue {
	map<char,int> error;
	map<string,int> errors;
	string label;
	vector<MyHDB> res;
	void GetType(string,string,vector<string> &,vector<string> &,vector<string> &, map<string, vector<string> > &);
	void its_error(char);
	void its_error(string);
	static bool force;
public:
	void error_report();
	Residue();
	Residue(string, string);
	virtual ~Residue();
	static void Force(){force=true;};
	friend std::ofstream & operator<<(std::ofstream & out, Residue & y){
		out << left << fixed << setw(4) << y.label << right << setw(5) << y.res.size() << "\n";
		for(unsigned int i=0;i<y.res.size();i++)  out << y.res[i];
		return out;
	}
	friend std::ostream & operator<<(std::ostream & out, Residue & y){
		out << left << fixed << setw(4) << y.label << right << setw(5) << y.res.size() << "\n";
		for(unsigned int i=0;i<y.res.size();i++)  out << y.res[i];
		return out;
	}
};

#endif /* RESIDUE_H_ */
