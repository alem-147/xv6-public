
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
			// this should make stat = 1
			exit(1);
		}
		else {
			wait(&stat);
		}
		printf(1,"my childs exit status was %d. I am a good waiter\n",stat);
}

void waitpidtest(void) {
	//	int i,stat;
//		int pid[5];
		
}

int main() {
	//exittest1(NULL);
	waittest();
	exit(0);
}
