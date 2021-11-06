#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
// #include "spinlock.h"
#include "proc.h"
// #include "pstat.h"




int sys_settickets(void){
    int number;

    if(argint(0,&number)<0)
            return -1;

    if(number<1)
         return -1;
         
  struct proc * p=myproc();
  acquire(&ptable.lock);
  _settickets(p,number);
  release(&ptable.lock);


  return 0;
}

int sys_getpinfo(void){

   struct pstat * state;
  struct proc * p;
  

  if(argptr(0,(void*)&state,sizeof(*state))<0)
     return -1;
  
  if(!state)//state is NULL
    return -1;

  acquire(&ptable.lock);
  for(p=ptable.proc; p<&ptable.proc[NPROC]; p++)
  {
    
    int indx= p-ptable.proc;//index= current process pointer- process at the beginning of ptable
    if(p->state!=UNUSED){
      state->pid[indx]=p->pid;     // the PID of each process
      state->inuse[indx]=p->inuse;   //whether this slot of the process table is inuse(1or0) 
      state->tickets[indx]=p->tickets; // the number of tickets this process has
      state->ticks[indx]=p->ticks;   //the number of ticks each process has accumulated
    }

  }
  release(&ptable.lock);

  return 0;
       
}


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
