

#include "cuda_computing.cuh"

#define THREADS_PER_BLOCK 128
#define BODIES_PER_THREAD 4 //only mutiples of 2

namespace Device {
	// CUDA global constants
	__device__ __constant__
		int NTHREADS;

////////////////////////////////////////////////////////////////////////////////////////////////////
// initializes device, detects hardware, number of threads per block
////////////////////////////////////////////////////////////////////////////////////////////////////
bool
Cuda_Computing::initDevice() {
	//check execution environment
	int deviceCount = 0;
	int device_handle = 0;
	errorCheckCuda(cudaGetDeviceCount(&deviceCount));

	if (0 == deviceCount) {
		std::cerr << "initDevice() : No CUDA device found." << std::endl;
		return false;
	}

	if (deviceCount > 1) {
		std::cerr << "initDevice() : Multiple CUDA devices found. Using first one." << std::endl;
	}

	// set the device
	errorCheckCuda(cudaSetDevice(device_handle));

	cudaDeviceProp device_props;
	errorCheckCuda(cudaGetDeviceProperties(&device_props, device_handle));
	//std::cerr << "Max CC: " << device_props.major << "   Min CC: " << device_props.minor << std::endl;

	// determine thread layout
	// num of threads on 1 block, thread layout per block
	blockSize = dim3(THREADS_PER_BLOCK, 1, 1);
	int numBlocks = N / THREADS_PER_BLOCK;
	if (0 != N % blockSize.x) numBlocks++;
	// number of blocks, block layout on grid
	gridSize = dim3(numBlocks, 1, 1);

	std::cerr << "num blocks = " << gridSize.x << " :: "
		<< "threads per Block = " << blockSize.x << std::endl;

	int nTh = THREADS_PER_BLOCK;

	errorCheckCuda(cudaMemcpyToSymbol(Device::NTHREADS, &blockSize.x, sizeof(int), 0, cudaMemcpyHostToDevice));
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// kernel entry point
////////////////////////////////////////////////////////////////////////////////////////////////////
float
Cuda_Computing::compute() {
	float time;
	cudaEvent_t start, stop;
	errorCheckCuda(cudaEventCreate(&start));
	errorCheckCuda(cudaEventCreate(&stop));
	errorCheckCuda(cudaEventRecord(start, 0));

	//CALL CUDA COMPUTATION

	//errorCheckCuda(cudaPeekAtLastError());
	errorCheckCuda(cudaDeviceSynchronize());
	errorCheckCuda(cudaEventRecord(stop, 0));
	errorCheckCuda(cudaEventSynchronize(stop));
	errorCheckCuda(cudaEventElapsedTime(&time, start, stop));

	return time;
}
