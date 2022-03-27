#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAXCHILDREN 10

int finish_rank[MAXCHILDREN];
int child_pids[MAXCHILDREN];

void 
clean_children()
{
	int i,child_return;
	for(i = 0; i < MAXCHILDREN; i++) {
		while((child_return = wait()) < 0);
		printf(1, "Child wait recieved. Returned: %d\n", child_return);
		finish_rank[i] = child_return;	
	}
}

int main() {
  int pid;
  int k, i;
  int x, z;

  x = 0;
  pid = 0;

  for ( k = 0; k < MAXCHILDREN; k++ ) {
    pid = fork ();
    if ( pid < 0) { 
      printf(1, "%d failed in fork!\n", getpid());
    } 
		if ((child_pids[k] = pid) > 0) {
      // parent
      //printf(1, "Parent %d creating child %d\n",getpid(), pid);
			if (k == 	MAXCHILDREN-1){
				clean_children();
				for(i = 0; i < MAXCHILDREN; i++) 
					printf(1,"finished %d, pid %d\n",i,finish_rank[i]);
				}
			continue;
      }
      else{
				update_priority(10+MAXCHILDREN-k); //later children should finish first
				for(z = 0; z < 1000000; z++)
	    			x = x + 5.2*10.1; //Useless calculation to consume CPU Time
      	printf(2,"Finished child %d\n",k);
				break;
			}
			
  }
  exit(22);
}
