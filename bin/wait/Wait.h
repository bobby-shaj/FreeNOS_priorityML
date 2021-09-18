#ifndef __BIN_SLEEP_SLEEP_H
#define __BIN_SLEEP_SLEEP_H

#include <POSIXApplication.h>

/**
 * @addtogroup bin
 * @{
 */

/**
 * Stop executing for some time.
 */
class Sleep : public POSIXApplication
{
  public:

    /**
     * Constructor
     *
     * @param argc Argument count
     * @param argv Argument values
     */
    Sleep(int argc, char **argv);

    /**
     * Destructor
     */
    virtual ~Sleep();

    /**
     * Execute the application.
     *
     * @return Result code
     */
    virtual Result exec();
};

/**
 * @}
 */

#endif /* __BIN_SLEEP_SLEEP_H */
