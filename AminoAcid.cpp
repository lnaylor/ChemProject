#include "AminoAcid.h"

AminoAcid::AminoAcid(string n) {
	name = n;
	if (name == "ALA") {
		propensity = 0.0;
	}
	else if (name == "ARG") {
		propensity = .21;
	}
	else if (name == "ASN") {
		propensity = .65;
	}
	else if (name == "ASP") {
		propensity = .69;
	}
	else if (name == "CYS") {
		propensity = .68;
	}
	else if (name == "GLU") {
		propensity = .40;
	}
	else if (name == "GLN") {
		propensity = .39;
	}
	else if (name == "GLY") {
		propensity = 1.0;
	}
	else if (name == "HIS") {
		propensity = .61;
	}
	else if (name == "ILE") {
		propensity = .41;
	}
	else if (name == "LEU") {
		propensity = .21;
	}
	else if (name == "LYS") {
		propensity = .26;
	}
	else if (name == "MET") {
		propensity = .24;
	}
	else if (name == "PHE") {
		propensity = .54;
	}
	else if (name == "PRO") {
		propensity = 3.16;
	}
	else if (name == "SER") {
		propensity = .50;
	}
	else if (name == "THR") {
		propensity = .66;
	}
	else if (name == "TRP") {
		propensity = .49;
	}
	else if (name == "TYR") {
		propensity = .53;
	}
	else if (name == "VAL") {
		propensity = .61;
	}
}

void AminoAcid::setName(string n) {
	name = n;
}

string AminoAcid::getName() {
	return name;
}

double AminoAcid::getPropensity() {
	return propensity;
}
