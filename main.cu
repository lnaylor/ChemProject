#include <cuda.h>
#include "AminoAcid.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#define _USE_MATH_DEFINES
#define BOLTZ_CONST .0019872041

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
using namespace std;

__global__ void sum4(double** pd_props, int size, double** pd_sums) {
	int i = threadIdx.x;
	while (i<size-3) {
	double sum = 0.0;
		for (int j = 0; j<4; j++) {
			sum =+ *pd_props[i];
		}
		*pd_sums[i] = sum;
		i++;
	}
}

__global__ void calcProp(double** pd_sums, double** pd_finalProps, int temp) {
	int i = threadIdx.x;
	*pd_finalProps[i] = pow(M_E, -1*(*pd_sums[i])/(BOLTZ_CONST*temp));
}

int main(void) {
	fstream dataFile;
	dataFile.open("aminoAcidList.txt", ios::in);

	thrust::host_vector<AminoAcid*> protein;
	string line;

	while (dataFile >> line) {
		protein.push_back(new AminoAcid(line));
	}
	dataFile.close();
	int temperature;
	cout << "What is the temperature?" << endl;
	cin >> temperature;

	thrust::host_vector<double*> props(protein.size());
	for (int i = 0; i<protein.size(); i++) {
		*props[i] = protein[i]->getPropensity();
	}

	thrust::device_vector<double*> d_props;
	double** pd_props = thrust::raw_pointer_cast(d_props.data());
	thrust::device_vector<double*> d_sums;
	double** pd_sums = thrust::raw_pointer_cast(d_sums.data());
	thrust::device_vector<double*> d_finalProps;
	double** pd_finalProps = thrust::raw_pointer_cast(d_finalProps.data());
	int d_size;
	int d_temp;
	
	int tempSize = 5;
	int *size = &tempSize;
	*size = protein.size();
	int propSize = 1;
	for (int k = 2; k<protein.size()-2; k++) {
		propSize += k;
	}

	cudaMalloc((void **) &d_props, propSize*sizeof(double));
	cudaMalloc((void **) &d_sums, propSize*sizeof(double));
	cudaMalloc((void **) &d_size, sizeof(int));
	cudaMalloc((void **) &d_temp, sizeof(int));
	cudaMalloc((void **) &d_finalProps, propSize*sizeof(double));

	thrust::host_vector<double*> sums(propSize);
	
	cudaMemcpy(&d_props, &props, protein.size()*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(&d_size, &size, sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(&d_temp, &temperature, sizeof(int), cudaMemcpyHostToDevice);

	sum4<<<1, propSize>>>(pd_props, d_size, pd_sums);
	calcProp<<<1, propSize>>>(pd_sums, pd_finalProps, d_temp);
	
	cudaMemcpy(&props, &d_props, propSize*sizeof(double), cudaMemcpyDeviceToHost);

	for (int i =0; i<props.size(); i++) {
		if (*props[i] > .05) {
			cout << *props[i] << endl;
		}
	}

	cudaFree(&d_finalProps);
	cudaFree(&d_props);
	cudaFree(&d_sums);
	cudaFree(&d_size);
	cudaFree(&d_temp);

	return 0;
}
