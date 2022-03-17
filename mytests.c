#include "types.h"
#include "stat.h"
#include "user.h"


/*
	
	Step 2 Test 1 
	test that syscall was created properly
	check output is:
	"i've updated someone with priority lvl %d\n"

*/

void 
update_priority_test1(int priority_level)
{
	update_priority(priority_level);
	exit(1);
}

int
main()
{
	update_priority_test1(23);
	exit(2);
}
