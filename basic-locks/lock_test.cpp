#include <iostream>
#include <thread>
#include <sys/time.h>
#include "counter.h"
using namespace std;

// Class to benchmark the lock when run with multiple threads
class Lock_Test
{
	private:
		static int THREADS;
		static int TIME;
		
		Counter lock_instance;	// Stores the lock instance
		long *opCount;		// Array to store no. of ops per thread;
		long totalOps;		// To store total ops done by all threads
		thread *thread_array;	// Array of threads to launch on the system
		timeval start_time;	// Stores the start time of operations.
	
	public:

		class BenchmarkNow: public thread
		{
			private:
				int pri_range = INT32_MAX - 1;
		};

		Lock_Test(int num_threads, int time)
		{
			THREADS = num_threads;
			TIME = time;

			thread_array = new thread[num_threads];
			opCount = new long[num_threads];
			totalOps = 0;
		}

		void testParallel()
};

int main()
{
	cout<<"Test code after a long time"<<endl;
	return 0;
}