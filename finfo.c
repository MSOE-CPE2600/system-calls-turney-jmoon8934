/***************************************************************************
* Filename: finfo.c
* Author: Jeric Moon
* Date: 10/30/2025
* Desc: Lab9 System Calls Part 3
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char* argv[])
{
    //check if arguments were provided
    if(argc < 2)
    {
        printf("Please enter in arguments in propper format.\n");
        //Format is ./executable <file>
        printf("Format is %s <file_name>\n", argv[0]);
    }

    //reccomended sys calls are stat/fstat/lstat. 
    //these utilize a stat structure
    struct stat file_data;
    //stat f-n returns info about the file in arg 1 into the buffer pointed to by the 2nd arg
    //returns -1 if erros.
    //file path is argv[1], file_data stat struct to hold data.
    if(stat(argv[1], &file_data) == -1)
    {
        char string[100];
        sprintf(string, "Failed to read data for file \"%s\"", argv[1]);
        perror(string);
        exit(1);
    }


    printf("File Type is: \n");
    //Switch case on file_data.st_mode & S_IFMT.
    //Stat struct holds a bunch of data, st_mode is the field that contains the file type and mode.
    //Credits to https://man7.org/linux/man-pages/man2/stat.2.html for the switch opperator and usage
    //S_IFMT is a bit mask for file type -> st_mode & S_IFMT only retains the value for the file type 
    switch (file_data.st_mode & S_IFMT)
    {
        case S_IFBLK:
            printf("Block device\n");
            break;
        case S_IFCHR:
            printf("Character device\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFIFO:
            printf("FIFO\n");
            break;
        case S_IFLNK:
            printf("Symlink\n");
            break;
        case S_IFREG: 
            printf("File\n");
            break;
        case S_IFSOCK:
            printf("Socket\n");
            break;
        default:
            printf("Unknown file");
    }

    //If else statements utilizing masking macro used for determining permission
    //I.E. S_IRUSR is a mask for owner [user] can read.
    printf("File Owner Permissions is: \n");
    if (file_data.st_mode & S_IRUSR)
    {
        printf("r"); 
    } else 
    { 
        printf("-");
    }
    if (file_data.st_mode & S_IWUSR)
    {
        printf("w"); 
    } else 
    { 
        printf("-");
    }
    if (file_data.st_mode & S_IXUSR)
    {
        printf("x"); 
    } else 
    { 
        printf("-");
    }
    printf("\n");

    //S_IRGRP is a mask for group can read.
    printf("File Group Permissions is: \n");
    if (file_data.st_mode & S_IRGRP)
    {
        printf("r"); 
    } else 
    { 
        printf("-");
    }
    if (file_data.st_mode & S_IWGRP)
    {
        printf("w"); 
    } else 
    { 
        printf("-");
    }
    if (file_data.st_mode & S_IXGRP)
    {
        printf("x"); 
    } else 
    { 
        printf("-");
    }
    printf("\n");

    //S_IROTH is a mask for others can read.
    printf("File Other Permissions is: \n");
    if (file_data.st_mode & S_IROTH)
    {
        printf("r"); 
    } else 
    { 
        printf("-");
    }
    if (file_data.st_mode & S_IWOTH)
    {
        printf("w"); 
    } else 
    { 
        printf("-");
    }
    if (file_data.st_mode & S_IXOTH)
    {
        printf("x"); 
    } else 
    { 
        printf("-");
    }
    printf("\n");

    //.st_uid = user/owner id
    printf("Owner ID: %d\n", file_data.st_uid);
    //.st_size is file size in bytes. Simple check to format it nicer if working in megabytes.
    int num_bytes = file_data.st_size;
    if(num_bytes % 1*10E6 > 0)
    {
        num_bytes = num_bytes / 1*10E6;
        printf("File Size in megabytes: %d\n", num_bytes);
    }
    else
    {
        printf("File Size in bytes: %d\n", num_bytes);
    }

    // stat contains timespec structs for Time of last access, Time of last modification, and Time of last status change.
    // pass this into a tm struct for easy parsing and printing
    struct tm *last_modification = localtime(&file_data.st_mtim.tv_sec);
    //store tm in string buffer for printing
    char modification_buffer[80];
    strftime(modification_buffer, sizeof(modification_buffer), "%Y-%m-%d %H:%M:%S", last_modification);
    printf("The date and time of last modification is %s\n", modification_buffer);

    return 0;
}