#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Sleep.h"

Sleep::Sleep(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Stop executing for some time");
    parser().registerPositional("SECONDS", "Stop executing for the given number of seconds");
}

Sleep::~Sleep()
{
}

Sleep::Result Sleep::exec()
{
    int sec = 0;

    // Convert input to seconds
    if ((sec = atoi(arguments().get("SECONDS"))) <= 0)
    {
        ERROR("invalid sleep time `" << arguments().get("SECONDS") << "'");
        return InvalidArgument;
    }

    // Sleep now
    if (sleep(sec) != 0)
    {
        ERROR("failed to sleep: " << strerror(errno));
        return IOError;
    }

    // Done
    return Success;
}
