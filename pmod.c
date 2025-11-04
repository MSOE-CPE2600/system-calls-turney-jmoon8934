/***************************************************************************
* Filename: pmod.c
* Author: Jeric Moon
* Date: 10/30/2025
* Desc: Lab9 System Calls Part 2
****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    //nice adds the provided integer to the "niceness" of the process
    //niceness basically is process scheduling order, higher niceness = later process
    nice(10);

    //timespec struc which holds a number of seconds and nanoseconds
    //define it to hold 1,837,272,638 nanoseconds or 1 second + 837,272,638 nanoseconds
    struct timespec sleep = {1, 837272638};
    //sleeps for the amount of time declared in first timespec struct param, writes the remaining into address of 2nd struct
    //2nd arg can be null to not store values.
    nanosleep(&sleep, NULL);
    printf("Thank you for running my program!\n");
    return 0;
}