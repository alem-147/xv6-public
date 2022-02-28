
#include "types.h"
#include "stat.h"
#include "user.h"
#define NULL 0

/* 
		exit must return an exit status on all user programs
		lets do some forking to confirm the proccess are exiting 
		with the proper exit statuses
*/
void exittest1(int status) {
	int pid,n;
	int fork_count = 3;
	
	printf(1,"I am the parent proccess, process 0\n");
	if (!(pid = fork())) { // parent goes past, child enters
		int process_count = 1;
		printf(1,"I am the child proccess, process 1\n");
		for( n=0;n<fork_count;n++) {
			process_count++;
			int pid = fork();
			if(pid) {
				wait(&status);
			}
			else {
				printf(1,"I am the Gchild proccess, process %d\n",process_count);
				exit(process_count);
			}
		
		}
		wait(&status);
		exit(1);
	}
	wait(&status);
	exit(0);
} 

/* 
	wait must be able to pass the exit status of its child to a pointer!
	lets see if we can do that
*/
void waittest(void) {
		int stat;
		if (fork() == 0) {
			// this should make stat = 82 
			exit(82);
		}
		else {
			wait(&stat);
		}
		printf(1,"my childs exit status was %d. I am a good waiter\n",stat);
}
/*
  must handle options of WNOHANG and 0 for options
  must check status passed
  must check that specific pid returned

		how to test if not our child
*/
void waitpidtest(void) {
	int i,stat;
	int fork_ret;
	int cpid;
	// fork 6 children
	for(i=0; i<6;i = i +1) {
		fork_ret = fork();
		if(fork_ret  == 0) { // for some reason ref pid[_] in any way breaks the loop 
			printf(1, "hi im child number: %d\n",i);
			int exit_stat = 100 + i;
			exit(exit_stat); //exit right away
		}
		cpid = waitpid(fork_ret,&stat,0);
		printf(1,"child with pid: %d, exited with status: %d\n",cpid, stat);
	} 
}

void waitpidtest1(void) {
	int i,stat;
	int fork_ret;
	int cpid;
	// fork 6 children
	for(i=0; i<6;i = i +1) {
		fork_ret = fork();
		if(fork_ret  == 0) { // for some reason ref pid[_] in any way breaks the loop 
			printf(1, "hi im child number: %d\n",i);
			int exit_stat = 100 + i;
			exit(exit_stat); //exit right away
		}
	}
	cpid = waitpid(6,&stat,0);//note the pids will range for 4 to 10
	printf(1,"child with pid: %d, exited with status: %d\n",cpid, stat);
	cpid = waitpid(8,&stat,0);//note the pids will range for 4 to 10
	printf(1,"child with pid: %d, exited with status: %d\n",cpid, stat);
}

int main() {
	//exittest1(NULL);
	//	waittest();
	//waitpidtest();
	waitpidtest1();
	exit(0);
}
