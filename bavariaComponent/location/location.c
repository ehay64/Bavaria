
#include "legato.h"
#include "interfaces.h"

static const char LOCATION_THREAD_NAME[] = "LOCATION_THREAD_NAME";

static le_thread_Ref_t locationThread;

static void *report_position(void *context)
{
    le_pos_FixState_t fixState = LE_POS_STATE_NO_FIX;

    int32_t latitude = 0;
    int32_t longitude = 0;
    int32_t altitude = 0;

    int32_t horizontalAccuracy = 0;
    int32_t verticalAccuracy = 0;

    //Connect this thread to the location service
    le_pos_ConnectService();

    while (true)
    {
        //Get the state of our location fix
        le_pos_GetFixState(&fixState);

        //If we're fixed
        if (fixState == LE_POS_STATE_FIX_2D || fixState == LE_POS_STATE_FIX_3D)
        {
            //Get our location
            le_pos_Get3DLocation(&latitude, &longitude, &horizontalAccuracy, &altitude, &verticalAccuracy);
            LE_INFO("Latitude: %f Longitude: %f Elevation: %f Horizontal Accuracy: %i", latitude / 1000000.0, longitude / 1000000.0, altitude / 1000.0, horizontalAccuracy);

            //Wait for a little bit
            sleep(5);
        }
        else
        {
            //Otherwise wait for a little bit less
            sleep(1);
        }
    }

    le_thread_Exit(NULL);
    return NULL;
}

le_result_t location_start(void)
{
    LE_INFO("Starting location thread");

    //Start location services
    le_posCtrl_Request();

    //Create the location thread
    locationThread = le_thread_Create(LOCATION_THREAD_NAME, report_position, NULL);

    //Start the location thread
    le_thread_Start(locationThread);

    return LE_OK;
}

le_result_t location_stop(void)
{
    LE_INFO("TODO: Stopping location thread");

    return LE_OK;
}
