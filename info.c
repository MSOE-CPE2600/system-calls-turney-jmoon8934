/***************************************************************************
* Filename: info.c
* Author: Jeric Moon
* Date: 10/30/2025
* Desc: Lab9 System Calls Part 1
****************************************************************************/
#include <time.h>
#include <stdio.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

#define SECONDS_PER_DAY 86400
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MINUTE 60

int main(int argc, char* argv[])
{
    //Timespec is a structure provided by time.h which "describes times in seconds & nanoseconds"
    //Used for a number of time related f-ns and syscalls, i.e. clock_gettime()
    struct timespec clock;
    
    clock_gettime(CLOCK_REALTIME, &clock);
    //Current time variable in unix in seconds
    long int time = clock.tv_sec;
    //Remove excess days worth of seconds
    time = (time%SECONDS_PER_DAY); 
    //Print time in seconds then time in ns all in one.
    //Time is mutually exclusive, ns has a limit of 999,999,999 max so it'll hold sub-seciond values. 
    //Printing "seconds nanoseconds" displays a string that is the time in nanoseconds with the second values shifted over.
    printf("Current time of day in nanoseconds is: %ld%ld\n", time, clock.tv_nsec);

    //utsname struct from #include <sys/utsname.h>, contains char[] that can hold system info/names
    //uname populates the struct with sysname[] (system name), nodename[] (network name), release[] (OS release),
    //version[] (OS version), machine[] (hardware type identifier), and domainname[] (NIS or YIP). <- These are "Network Information Service", an "abritrary name which identifies a group of machines sharing NIS data"
    struct utsname utsname;
    //Check to see if uname() erorred when retrieving/storing info.
    //If it does, perror and terminate the program
    if(uname(&utsname) != 0)
    {
        perror("uname");
        exit(1);
    }
    //gethostname f-n enables the user to get the system's host name
    //Network node name is the same as the host name.
    char hostname[255];
    //Check to see if gethostname errored
    //If it did, perror & terminate the prgroam.
    if(gethostname(hostname, 255) != 0)
    {
        perror("hostname");
        exit(1);
    }
    printf("The system's hostname is: %s\n", hostname);
    printf("The system's network name is: %s\n", utsname.nodename);
    //Observe how nodename & hostname return the same. Two different ways to access the same information.
    printf("The system's OS's name is: %s\n", utsname.sysname);
    printf("The system's release and version is %s, %s\n", utsname.release, utsname.version);
    printf("The system's hardware type is %s\n", utsname.machine);

    //get_nprocs_conf() vs get_nprocs(). One returns number of processors configured by the system, one returns number of AVALIABLE processors.
    //These numbers may differ.
    printf("The number of processors in the system is %d\n", get_nprocs_conf());
    printf("The number of avaliable processors is %d\n", get_nprocs());

    //sysconf and libc comes with a bunch of macros to int values.
    //sysconf can get a ton of system information, but only returns 1 value at a time depending on passed in macro.
    //relevant macros are used, and var names help describe their functionality.
    long int num_pages = sysconf(_SC_PHYS_PAGES);
    long int avail_pages = sysconf(_SC_AVPHYS_PAGES);
    long int bytes_per_page = sysconf(_SC_PAGESIZE);
    long int num_bytes = num_pages*bytes_per_page;
    long int avail_bytes = avail_pages*bytes_per_page;
    if(num_bytes < 0)
    {
        perror("num of mem bytes underflow");
        exit(1);
    }
    if(avail_bytes < 0)
    {
        perror("avaliable num of mem bytes underflow");
        exit(1);
    }
    printf("The number of bytes of memory is %ld\n", num_bytes);
    printf("The number of avaliable bytes of memory is %ld\n", avail_bytes);
    return 0;
}