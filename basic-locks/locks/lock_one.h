/*
	Basic lock

	Author: Srikar
*/

#include "../include/base_lock.h"

using namespace std;

class LockOne: public baseLock
{
	bool flag[2];
	
	void lock(int threadID)
	{
		int i = threadID;
		int j = 1 - i;
		flag[i] = true;

		// Wait to acquire lock
		while (flag[j]);
	}

	void unlock(int threadID)
	{
		int i = threadID;
		flag[i] = false;
	}
};