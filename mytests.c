
#include "types.h"
#include "stat.h"
#include "user.h"


/* 
		exit must return an exit status on all user programs
		lets do some forking to confirm the proccess are exiting 
		with the proper exit statuses
*/
void exittest(void) {
	int pid,n,stat;
	int fork_count = 3;
	
	printf(1,"I am the parent proccess, process 0\n");
	if (!(pid = fork())) { // parent goes past, child enters
		int stat;
		int process_count = 1;
		printf(1,"I am the child proccess, process 1\n");
		for( n=0;n<fork_count;n++) {
			process_count++;
			int pid = fork();
			if(pid) {
				wait(&stat);
			}
			else {
				printf(1,"I am the Gchild proccess, process %d\n",process_count);
				exit(process_count);
			}
		
		}
		wait(&stat);
		exit(1);
	}
	wait(&stat);
	exit(0);
} 

void waittest(void) {

}

int main() {
	exittest();
	exit(0);
}
