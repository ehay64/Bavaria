
#include "legato.h"
#include "interfaces.h"

#include "location/location.h"

static void do_forever()
{
    while (true)
    {
        LE_INFO("Main loop, continuing");

        sleep(5);
    }
}

COMPONENT_INIT
{
    //Setup location reporting
    location_start();

    //Do forever
    do_forever();
}
