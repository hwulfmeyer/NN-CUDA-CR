


#ifndef _CUDA_COMPUTING_H_
#define _CUDA_COMPUTING_H_

#include <vector>
#include <iostream>
#include <algorithm>

#include "device_launch_parameters.h"
#include "cuda.h"
#include "cuda_runtime.h"
#define __CUDA_INTERNAL_COMPILATION__
#include "math_functions.h"
#undef __CUDA_INTERNAL_COMPILATION__


#define errorCheckCuda(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}

class Cuda_Computing {
public:
	//constructor
	Cuda_Computing();

	//destructor
	~Cuda_Computing() {};

	bool initDevice();
	
	float compute();


private:
	const int N;			// number of bodies
	dim3 gridSize;			// The actual grid size needed, based on input size (num blocks)
	dim3 blockSize;			// Suggested block size to achieve maximum occupancy.(num threads per block)


};

#endif