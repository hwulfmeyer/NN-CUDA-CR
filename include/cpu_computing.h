

#ifndef _CPU_COMPUTING_H_
#define _CPU_COMPUTING_H_

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>



class Cpu_Computing {
public:

	//constructor
	Cpu_Computing();
	//destructor
	~Cpu_Computing();

	void setThreads();
	void setThreads(unsigned int nthreads);

private:

	// number of threads
	unsigned int numThreads;
	// mutex to control access to the arrays
	std::mutex mutexTiles;
	/* Used to lock/unlock threads via
	* 	mutexTiles.lock();
	*	mutexTiles.unlock();
	*/

};

#endif