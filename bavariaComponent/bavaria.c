#include "legato.h"
#include "interfaces.h"

static void wait_for_fix()
{
    le_posCtrl_Request();

    while (true)
    {
        le_pos_FixState_t fixState = LE_POS_STATE_NO_FIX;
        le_pos_GetFixState(&fixState);

        if (fixState == LE_POS_STATE_FIX_2D || fixState == LE_POS_STATE_FIX_3D)
        {
            LE_INFO("Location fixed");
            break;
        }

        LE_INFO("Location not fixed yet");
        sleep(5);
    }
}

static void report_position()
{
    int32_t latitude = 0;
    int32_t longitude = 0;
    int32_t altitude = 0;

    int32_t horizontalAccuracy = 0;
    int32_t verticalAccuracy = 0;

    le_pos_Get3DLocation(&latitude, &longitude, &horizontalAccuracy, &altitude, &verticalAccuracy);
    LE_INFO("Latitude: %f Longitude: %f Elevation: %f Horizontal Accuracy: %i", latitude / 1000000.0, longitude / 1000000.0, altitude / 1000.0, horizontalAccuracy);
}

static void do_forever()
{
    while (true)
    {
        report_position();

        sleep(5);
    }
}

COMPONENT_INIT
{
    //Setup positioning
    wait_for_fix();

    //Do forever
    do_forever();
}
