/*
 * Residue.cpp
 *
 *  Created on: Feb 11, 2012
 *      Author: marchi
 */

#include "Residue.h"
bool Residue::force=false;

void Residue::its_error(char c){
	if(error.count(c)) {
		error[c]++;
		return;
	}
	error[c]=1;
}
void Residue::its_error(string s){
	if(errors.count(s)) {
		errors[s]++;
		return;
	}
	errors[s]=1;
}
void Residue::error_report(){
	if(error.size()){
		typedef map<char,int>::iterator Miterator;
		Miterator ite;
		for(ite=error.begin();ite != error.end();++ite){
			cerr << " Cannot assign hydrogens to atoms of element " << ite->first ;
			cerr << ", which occurred "<< fixed << ite->second << " times " << " \n";
		}
	}
	if(errors.size()){
		typedef map<string,int>::iterator Miterator;
		Miterator ite;
		if(force)
			for(ite=errors.begin();ite != errors.end();++ite){
				cerr <<  fixed << ite->second << " warning(s) found : "<< ite->first << "\n";}
		else
		for(ite=errors.begin();ite != errors.end();++ite){
			cerr <<  fixed << ite->second << " fatal error(s) found : "<< ite->first << "\n";}
	}
	if((error.size() || errors.size()) && !force) exit(1);
}

void Residue::GetType(string label0,string atom,vector<string> & neighs,vector<string> & hs,
		vector<string> & nhs, map<string, vector<string> > & conect){

	int ntot=neighs.size();
	int nh=hs.size();
	if(!nh) return;
	int mult=0;
	int ret=0;
	string & y=atom;
	if(y[0] != 'C' &&y[0] != 'N' &&y[0] != 'O' && y[0] != 'S') its_error(y[0]);
	vector<string> sout;
	string tmp;
	string::iterator its;

	Connected tm0;
	if(y[0] =='C'){
		switch(ntot){
		case 4:
			switch(nh){
			case 3:
				tmp=hs[0].substr(0,hs[0].length()-1);
				tm0(conect[nhs[0]],atom,'H');
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				sout.insert(sout.end(),tm0[0]);
				ret=4;
				mult=3;
				break;
			case 2:
				tmp=hs[0].substr(0,hs[0].length()-1);
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				mult=2;
				ret=6;
				break;
			case 1:
				tmp=hs[0];
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				mult=1;
				ret=5;
				break;
			}
			break;
		case 3:
			switch(nh){
			case 2:
				tmp=hs[0].substr(0,hs[0].length()-1);
				tm0(conect[nhs[0]],atom,'H');
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				sout.insert(sout.end(),tm0[0]);
				mult=2;
				ret=3;
				break;
			case 1:
				tmp=hs[0];
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				mult=1;
				ret=1;
				break;
			}
			break;
		case 2:
			ret=4;
			break;
		}
	} else if(y[0] == 'N'){
		switch(ntot){
		case 4:
			switch(nh){
			case 3:
				tmp=hs[0].substr(0,hs[0].length()-1);
				tm0(conect[nhs[0]],atom,'H');
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				sout.insert(sout.end(),tm0[0]);
				ret=4;
				mult=3;
				break;
			case 2:
				tmp=hs[0].substr(0,hs[0].length()-1);
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				mult=2;
				ret=6;
				break;
			case 1:
				tmp=hs[0];
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				mult=1;
				ret=5;
				break;
			}
			break;
		case 3:
			switch(nh) {
			case 2:
				tmp=hs[0].substr(0,hs[0].length()-1);
				tm0(conect[nhs[0]],atom,'H');
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				sout.insert(sout.end(),tm0[0]);
				mult=2;
				ret=3;
				break;
			case 1:
				tmp=hs[0];
				sout.push_back(tmp);
				sout.push_back(atom);
				sout.insert(sout.end(),nhs.begin(),nhs.end());
				mult=1;
				ret=1;
				break;
			}
			break;
		}
	}else if(y[0] == 'O'){
		switch(nh){
		case 1:
			tmp=hs[0];
			tm0(conect[nhs[0]],atom,'H');
			sout.push_back(tmp);
			sout.push_back(atom);
			sout.insert(sout.end(),nhs.begin(),nhs.end());
			sout.insert(sout.end(),tm0[0]);
			mult=1;
			ret=2;
			break;
		case 2:
			tmp=hs[0].substr(0,hs[0].length()-1);
			sout.push_back(tmp);
			sout.push_back(atom);
			mult=2;
			ret=7;
			break;
		}
	}else if(y[0] == 'S'){
		tmp=hs[0];
		tm0(conect[nhs[0]],atom,'H');
		sout.push_back(tmp);
		sout.push_back(atom);
		sout.insert(sout.end(),nhs.begin(),nhs.end());
		sout.insert(sout.end(),tm0[0]);
		mult=1;
		ret=2;
	}
	MyHDB tmp1(mult,ret, sout);
	res.push_back(tmp1);
}

Residue::Residue() {
	// TODO Auto-generated constructor stub

}

Residue::Residue(string label0, string sstr): label(label0) {
	map<string,vector<string> > conect;
    MyToken mtok(sstr,re_squares);
    int ia=-1;
    try{
    	for(unsigned int i=0;i<mtok.size();i++)
    		if(mtok.GetLabel(i).find("bonds") != string::npos) ia=i;
    	if(ia==-1) throw "Bonds not present in the .rtp file! Why do you need hydrogens??";
    }
    catch(const char * s){
    	cout << s << endl;
    	return;
    }
    MyToken tok(mtok[ia],re_sep0);

    for (unsigned int i=0;i<tok.size();i++){
    	trim(tok[i]);
    	if(tok[i].empty()) continue;
		if(tok[i].find(';') != string::npos){
    		tok[i].erase(tok[i].find(';'),tok[i].length());
    	}
    	if(tok[i].empty()) continue;

        vector<string> ss;
    	split(ss,tok[i],is_any_of("\t "), token_compress_on);
    	string & str1=ss[0];
    	string & str2=ss[1];

    	for(unsigned int o=0;o<ss.size();o++)
    		if(ss[o].find('+') != string::npos || ss[o].find('-') != string::npos )
    			if(force)
    				its_error(" Errors can occur for hydrogens across protein residues\nor polymers subunits ");
    			else
    				its_error(" Cannot handle hydrogens across protein residues\nor polymers subunits ");

    	map<string, vector<string> >::iterator itc=conect.find(str1);
    	if(itc != conect.end()) {
    		itc->second.push_back(str2);
        } else {
        	vector<string> tmp;
        	tmp.push_back(str2);
        	conect[str1]=tmp;
        }
    	itc=conect.find(str2);
    	if(itc != conect.end()) {
    		itc->second.push_back(str1);
        } else {
        	vector<string> tmp;
        	tmp.push_back(str1);
        	conect[str2]=tmp;
        }

    }

    map<string, vector<string> >::iterator itc;

    for(itc=conect.begin();itc!=conect.end();++itc){
    	if(*itc->first.begin() == 'H') continue;
    	vector<string> & neighs=itc->second;
    	string atom=itc->first;
    	vector<string> hs,nhs;

    	for(unsigned int ia=0;ia<neighs.size();ia++)
    		if(*neighs[ia].begin() == 'H') {
    			hs.push_back(neighs[ia]);
    		} else {
    			nhs.push_back(neighs[ia]);
    		}
    	GetType(label,atom,neighs,hs,nhs,conect);
    }

}

Residue::~Residue() {
	// TODO Auto-generated destructor stub
}

