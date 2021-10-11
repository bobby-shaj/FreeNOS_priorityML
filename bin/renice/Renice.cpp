
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Renice.h"

int newPriority;
int processID;

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Changes the priority level of a process");
    parser().registerPositional("PID", "Process ID of the process to change priority of");
    newPriority = atoi(argv[1]);
    processID = atoi(argv[2]);
}

Renice::~Renice()
{
}

Renice::Result Renice::exec()
{
    printf("processID = %d\n", processID);
    int stat_loc
    int result = renicepid(processID, &stat_loc, newPriority, 0);

    if (result == -1) {
    	printf("Process priority could not be changed\n");
    }
    else if (result == processID) {
    	printf("New priority = %d\n", newPriority);
    }

    // Done
    return Success;
}

