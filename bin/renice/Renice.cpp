
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Renice.h"
#include "sys/renice.h"
#include <ProcessClient.h>

int newPriority;
int processID;

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Changes the priority level of a process");
    parser().registerPositional("Priority", "New priority of the process");
    parser().registerPositional("PID", "Process ID of the process to change priority of");
    parser().registerFlag('n', "priority", "Specifies the new priority of the process");
    newPriority = atoi(argv[2]);
    processID = atoi(argv[3]);
}

Renice::~Renice()
{
}

Renice::Result Renice::exec()
{
    printf("processID = %d\n", processID);
    printf("newPriority = %d\n", newPriority);
    bool result;
    ProcessClient process;

    // Check that input priority is valid
    if (newPriority < 1 || newPriority > 5) {
        result = false;
        printf("New priority not valid.\n");
    }
    else {
        process.setPriority(processID, newPriority);
        result = true;
        printf("Priority is valid.\n");
    }
    
    // Check and print result
    if (result == true) {
        printf("Priority successfully changed.\n");
    }
    else {
        printf("Process priority could not be changed.\n");
    }

    // Done
    return Success;
}

