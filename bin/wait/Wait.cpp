#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"
#include "sys/wait.h"

int processID;

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Waits for a background process to finish and return");
    parser().registerPositional("PID", "Process ID of the process to wait for");
    processID = atoi(argv[1]);
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    printf("processID = %d\n", processID);
    int stat_loc;
    int result = waitpid(processID, &stat_loc, 0);
    printf("result = %d\n", result);

    if (result == -1) {
        printf("Process did not exit properly.\n");
    }
    else if (result == processID) {
        printf("Process successfully completed.\n");
    }

    // Done
    return Success;
}
