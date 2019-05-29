
#include "legato.h"
#include "interfaces.h"

#include "location/location.h"

static void do_forever()
{
    Location location;

    while (true)
    {
        location_get(&location, 10);

        LE_INFO("Main loop, continuing");

        sleep(5);
    }
}

COMPONENT_INIT
{
    //Do forever
    do_forever();
}
