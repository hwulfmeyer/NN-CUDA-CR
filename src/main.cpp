
#include <iostream>
#include <string>
#include "cuda_computing.cuh"
#include "cpu_computing.h"


void
compute_cpu();

void
compute_gpu();

int
main(int argc, char** argv)
{
	return 0;
}


void compute_cpu()
{
	Cpu_Computing cpu_computer;
	cpu_computer.setThreads();
}

void compute_gpu()
{
	Cuda_Computing cuda_computer;
	cuda_computer.initDevice();
}

