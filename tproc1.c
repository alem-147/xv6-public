#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

/*

tests that the system calls getting time signitures work

*/

// do something that takes a long time then get time sig for single proc
int
single()
{
	
	int pid = fork();
	if(pid == 0) {
		int i,j,k,x = 0;
		for (i = 0; i < 10; i++){
			for(j = 0; j < i; j++){
				for(k = 0; k < j; k++){
					x = x + 5.2*i + j -3*k;
				}
			}
		}
	printf(1, "finished running\n");
	exit(0);
	}
	printf(1, "forked pid%d\n",pid);
	wait();
	return pid;
}

int 
main() 
{
	int pid = single();
	int mypid = getpid();
	printf(2,"fork TT: %d, WT: %d\n",turnaround_time(pid),waiting_time(pid));
	printf(2, "my TT %d, WT: %d\n",turnaround_time(mypid),waiting_time(mypid));

	exit(1);
}
