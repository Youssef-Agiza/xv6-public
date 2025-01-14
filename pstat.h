#ifndef PSTAT_H
#define PSTAT_H
#include "param.h"

struct pstat{
    int inuse[NPROC]; //whether this slot of the process table is inuse(1or0) 
    int tickets[NPROC]; // the number of tickets this process has
    int pid[NPROC]; // the PID of each process
    int ticks[NPROC]; //the number of ticks each process has accumulated
};
#endif