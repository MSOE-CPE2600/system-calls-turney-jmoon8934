/***************************************************************************
* Filename: info.c
* Author: Jeric Moon
* Date: 10/30/2025
* Desc: Lab9 System Calls Part 1
****************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    //local pid var to hold
    int pid;
    //if an argument is provided, assign pid to the arg
    if(argc > 1)
    {
        pid = atoi(argv[1]);
    }
    else
    {
        //if not, just get pid of current process
        pid = getpid();
    }
    //get priority gets the priority of the passed in type, and for who.
    //PRIO_PROCESS indicates the "type" is for the calling process
    //PRIO_PGRP for a group id, PRIO_USER for a user ID.
    //Clear errno before and check it after, as -1 is a legitimate result.
    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);
    //check to see if getpriority errored, check to see if it could find the PID.
    if(errno != 0)
    {
        //if it can't find the PID, then error and leave.
        perror("Error with passed in PID, value cannot be found");
        exit(1);
    }
    //print out priority, and PID in event user didn't provide one.
    printf("The process priority, with PID %d, is %d\n", pid, priority);

    //return the scheduling policy of the process specified by pid. PID is confirmed to exist by this point.
    int sched = sched_getscheduler(pid);
    
    return 0;
}