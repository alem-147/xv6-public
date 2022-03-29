#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
	int exit_status;
  argint(0, &exit_status);
	//cprintf("exiting with status %d\n",exit_status); 
  exit(exit_status);// what to put in here
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
	return uptime();
}

int sys_update_priority(void)
{
	int priority_level;
	argint(0,&priority_level);
	update_priority(priority_level);
	return priority_level;
}

int
sys_turnaround_time(void)
{
	int proc_id;
	argint(0,&proc_id);
	return turnaround_time(proc_id);
}

int
sys_waiting_time(void)
{
	int proc_id;
	argint(0,&proc_id);
	return waiting_time(proc_id);
}
