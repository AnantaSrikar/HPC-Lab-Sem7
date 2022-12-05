/*
	Classes of locks to be tested

	Author: Srikar
*/
#include <iostream>
#include "lock_one.h"
using namespace std;

class Counter
{
	private:
			class LockInstance
			{
				public:
					
					int count;
					baseLock *lock;
					LockInstance(int count)
					{
						this -> count = count;
						this -> lock = new LockOne();
						//this.lock=new ReentrantLock();
						//this.lock=new LockOne();
						//this.lock=new Peterson();
						//this.lock=new TTASLock();
						// this.lock=new BackoffLock();
						//this.lock=new ALock(8);
						//this.lock=new CLHLock();
						//this.lock=new MCSLock();
					}

					void Lock() {lock -> lock();}
					void Unlock() {lock -> unlock();}
			};

			LockInstance *head;
	
	public:
		Counter()
		{
			head = new LockInstance(0);
		}

		void inc()
		{
			head -> Lock();
			head -> count = head -> count + 1;
			head -> Unlock();
		}

		void display()
		{
			cout<<"\t"<<head -> count<<"\n";
		}
};