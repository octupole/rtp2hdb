//============================================================================
// Name        : rtp2hdb.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/program_options.hpp>
#include "MyToken.h"

namespace po = boost::program_options;
using namespace std;

#include <fstream>
#include <iterator>
#include <string>
#include "Residue.h"
#include "myTools.h"
using std::string;

int main(int ac, char* av[])
{
    string fileI,fileO;
    bool verbose=false;
    bool force=false;
    try {
        po::options_description desc("Allowed options:");
        po::variables_map vm;
        desc.add_options()
            ("help,h", "produce help message")
            ("verbose,v", "verbose mode")
            ("force,f","force to find hydrogens in protein residues and polymer units. Results will be wrong "
            		"for those hydrogens. It might be wrong for others.")
            ("rtp,i", po::value<string>(&fileI),"rtp file to process")
            ("hdb,o", po::value<string>(&fileO),"hdb file to generate")
        ;

        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
        if (vm.count("help")) {
            cout << desc << "\n";
            return 1;
        }
        if (vm.count("force")) {
            force=true;
        }
        if(!vm.count("rtp")){
            cout << desc << "\n";
            return 1;
        }
        if(vm.count("verbose")) verbose=true;
        if(fileI.find(".rtp") == string::npos) fileI.append(".rtp");

        if(!vm.count("hdb")){
        	fileO=fileI;
        	fileO.replace(fileO.find("rtp"),3,"hdb");
        }
        if(fileO.find(".hdb") == string::npos) fileO.append(".hdb");

        if(verbose) {
        	cout << "Output rtp filename was set to " << fileI << ".\n";
        	cout << "Output hdb filename was set to " <<  fileO << ".\n";
        }
    }
    catch(std::exception & e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    if(force) Residue::Force();
    ifstream ifs(fileI.c_str());
    ofstream ofs(fileO.c_str());

    if(!ifs){cout << "Could not open input file!\n";}
    stringstream ss;
    ss<< ifs.rdbuf();
    regex re("\\[ ([A-Z][A-Z0-9]*) \\]");

    string sstr=ss.str();
    vector<string> sstrs=mySplit(ss.str());
	boost::smatch what;

    for(auto sstr: sstrs){
    	MyToken tok(sstr,re);
    	for(unsigned int i=0;i<tok.size();i++){
    		Residue g(tok.GetLabel(i),tok[i]);
    		g.error_report();
    		ofs << g ;
    		if(verbose) cout << g;
    	}
    }
    cout << "Gromacs hydrogen bond file \"" << fileO << "\" has been created \n";
    return 0;
}
