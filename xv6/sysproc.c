#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

//  variable storing the number of read attempts
// whence the kernel boots
extern int read_count;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
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
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//  returns the number of active processes
int sys_getProcCount(void) {
  return getProcCount();
}

int sys_getReadCount(void) {
  return getReadCount();
}

int sys_clone(void) {
  char *stack;
  if (argptr(0, &stack, sizeof (void*)) < 0)
    return -1;
  return clone((void*) stack);
}

int sys_join(void) {
  return join();
}

int sys_setPriority(void)
{
  int priority;
  if (argint(0, &priority) < 0)
    return -1;
  else
    return setPriority(priority);
}

int sys_changePolicy(void)
{
  int policy;
  if (argint(0, &policy) < 0)
    return -1;
  else
    return changePolicy(policy);
}

int sys_getBurstTime(void)
{
  return getBurstTime();
}

int sys_getTurnAroundTime(void)
{
  return getTurnAroundTime();
}

int sys_getWaitingTime(void)
{
  return getWaitingTime();
}