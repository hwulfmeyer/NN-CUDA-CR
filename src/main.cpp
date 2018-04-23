
#include <iostream>
#include <string>
#include "cuda_computing.cuh"
#include "cpu_computing.h"


void
compute_cpu();

void
compute_gpu();


void 
readData();


int
main(int argc, char** argv)
{
	compute_cpu();

	std::cout << "Everything done!";
	getchar();
	return 0;
}


void compute_cpu()
{
	Cpu_Computing computer;
	computer.setThreads();
}

void compute_gpu()
{
	Cuda_Computing computer;
	computer.initDevice();
}

void readData()
{

}

