#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

// (Added by AmirInt) variable storing the number of read attempts
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

// (Added by AmirInt) returns the number of active processes
int sys_getProcCount(void) {
  return getProcCount();
}

// (Added by AmirInt) returns the number of read attempts whence
// the kernel boots
int sys_getReadCount(void) {
  return getReadCount();
}

// (Added by AmirInt) creates a thread and returns the thread ID
int sys_thread_create(void) {
  // Fetching the argument passed to the 'thread_create' function
  // which is the address of the allocated stack.
  char *stack;
  if (argptr(0, &stack, sizeof (void*)) < 0)
    return -1;
  return thread_create((void*) stack);
}

// (Added by AmirInt) makes the calling process to wait for its threads
int sys_thread_wait(void) {
  return thread_wait();
}

//(added by hadiinz)
int 
sys_setPriority(void)
{
  int priority;
  if (argint(0, &priority) < 0)
    return -1;
  else
    return setPriority(priority);
}

int 
sys_changePolicy(void)
{
  int policy;
  if (argint(0, &policy) < 0)
    return -1;
  else
    return changePolicy(policy);
}

int 
sys_getCBT(void)
{
  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  else
    return getCBT(pid);
}

int 
sys_getTurnAroundTime(void)
{
  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  else
    return getTurnAroundTime(pid);
}

int 
sys_getWaitingTime(void)
{
  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  else
    return getWaitingTime(pid);
}

int sys_wait_findTimes(void)
{
  int *arrayTime;
  //check the pointer ,points to valid address
  if (argptr(0, (void *)&arrayTime, sizeof(*arrayTime)) < 0)
  {
    return -1;
  }
  else
  {
    return wait_findTimes(arrayTime);
  }
}