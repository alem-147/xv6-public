
#include "types.h"
#include "stat.h"
#include "user.h"



/* 
		exit must return an exit status on all user programs
		lets do some forking to confirm the proccess are exiting 
		with the proper exit statuses
*/
void exittest(void) {
	int pid,n;
	int fork_count = 3;
	
	printf(1,"I am the parent proccess, process 0");
	if (!(pid = fork())) { // parent goes past, child enters
		int process_count = 1;
		printf(1,"I am the child proccess, process n");
		for( n=0;n<fork_count;n++) {
			process_count++;
			int pid = fork();
			if(pid) {
				continue;
			}
			else {
				printf(1,"I am the Gchild proccess, process n");
				exit(process_count);
			}
		exit(process_count);
		}
	}
	
} 

void waittest(void) {

}

int main() {
	exittest();
	exit(0);
}
