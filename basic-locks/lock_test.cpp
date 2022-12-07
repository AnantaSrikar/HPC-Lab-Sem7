#include <iostream>
#include <thread>
#include <sys/time.h>
#include <string>
#include "counter.h"
using namespace std;

void runThread(int thread_id, Counter *lock_instance, struct timeval start_time, long *opCount)
{
	long count = 0;
	struct timeval end_time;

	gettimeofday(&end_time, NULL);

	for(long i = 0; i < end_time.tv_usec - start_time.tv_usec; i++)
	{
		lock_instance -> inc();	// Lock and unlock for a thread
		count++;		// Count the number of times it was done

		if(count % 100 == 0)
			gettimeofday(&end_time, NULL);
	}

	opCount[thread_id] = count;
}

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
		struct timeval start_time;	// Stores the start time of operations.
	
	public:
		Lock_Test(int num_threads, int time)
		{
			THREADS = num_threads;
			TIME = time;

			thread_array = new thread[num_threads];
			opCount = new long[num_threads];
			totalOps = 0;
		}

		void testParallel()
		{
			gettimeofday(&start_time, NULL);
			
			// Initializing and launching all the threads
			for(int i = 0; i < THREADS; i++)
				thread_array[i] = thread(runThread, i, &lock_instance, start_time, opCount);

			for(int i = 0; i < THREADS; i++)
				thread_array[i].join();
		}

		long totalOperations()
		{
			for(int i = 0; i < THREADS; i++)
				totalOps += opCount[i];
			
			return totalOps;
		}

		void display()
		{
			lock_instance.display();
		}

		string getLockName()
		{
			return typeid(lock_instance).name();
		}
};

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		cout<<"Invalid number of arguments, exitting..."<<endl;
		return -1;
	}

	int num_threads = stoi(argv[1]);
	int runtime = stoi(argv[2]);

	Lock_Test lock_test(num_threads, runtime);

	// Running the benchmark!
	lock_test.testParallel();
	
	long total_ops = lock_test.totalOperations();
	double throughput = (total_ops / (1000000 * runtime)) * 1000;	//Millions of operations per sec
	
	// Displaying the results
	cout<<"c_name:\t"<<lock_test.getLockName()<<endl;
	cout<<"num_threads:\t"<<num_threads<<endl;
	cout<<"throughput:\t"<<throughput;
	cout<<"totalOps:\t"<<total_ops;

	lock_test.display();


	return 0;
}