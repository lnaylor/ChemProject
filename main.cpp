#include "AminoAcid.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#define _USE_MATH_DEFINES
#define BOLTZ_CONST 1.9872041*pow(10, -3) 

using namespace std;

double calculateProp(double sum, double temp) {
	double power = -1* sum/(BOLTZ_CONST*temp);
	return pow(M_E, power);
}

int main(int argc, const char * argv[]) {
	fstream dataFile;
	dataFile.open ("aminoAcidList.txt", ios::in);

	vector<AminoAcid*> protein;
	string line;

	while (dataFile >> line) {
		protein.push_back(new AminoAcid(line));
	}
	dataFile.close();

	int temperature;
	cout << "What is the temperature? ";
	cin >> temperature;
	
	vector<double> maxProps;
	vector<int> bottom;
	vector<int> top;

	for (int k=0; k<protein.size()-1; k++) {
		for (int j=k+3; j<protein.size(); j++) {
			double sumOfProps = 0.0;
			for (int i=k; i<j+1; i++) {
				sumOfProps += protein.at(i)->getPropensity();
			}
			if (calculateProp(sumOfProps, temperature)>.05) {
				maxProps.push_back(calculateProp(sumOfProps, temperature));
				bottom.push_back(k);
				top.push_back(j);
			}
		}
	}

	cout << "Highest propensities\n";
	for (int i = 0; i<maxProps.size(); i++) {
		cout << "Protein " << bottom.at(i)+1 << " to " << top.at(i)+1 << "(" << protein.at(bottom.at(i))->getName() << " to " << protein.at(top.at(i))->getName() << "): " << maxProps.at(i) << ".\n";
	}

	return 0;
}
