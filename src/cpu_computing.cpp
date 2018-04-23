

#include "cpu_computing.h"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> tpoint;
/*
tpoint t_start = std::chrono::high_resolution_clock::now();

tpoint t_end = std::chrono::high_resolution_clock::now();

return std::chrono::duration<float, std::milli>(t_end - t_start).count();

*/


// constructor, copies all the stuff to this class
Cpu_Computing::Cpu_Computing(){
}


// destructor, deletes our dynamic arrays
Cpu_Computing::~Cpu_Computing() {
};


// determines number of threads according to hardware
void
Cpu_Computing::setThreads() {
	// determine available hardware capabilities
	unsigned int nthreads = std::thread::hardware_concurrency();
	if (nthreads == 0) {
		std::cerr << "Couldn't detect hardware capabilities, number of threads set to ONE." << std::endl;
		nthreads = 1;
	}
	setThreads(nthreads);
}


// set number of threads to an arbitrary value
void
Cpu_Computing::setThreads(unsigned int nthreads) {
	this->numThreads = nthreads;

	std::cout << "Cpu_Computing::Cpu_Computing() - Using " << numThreads << " threads." << std::endl;
}

