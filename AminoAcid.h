#ifndef _AminoAcid_
#define _AminoAcid_

#include <iostream>
using namespace std;

class AminoAcid {

private:
	string name;
	double propensity;

public:
	AminoAcid(string);
	void setName(string);
	string getName();
	double getPropensity();
};

#endif
