
#include "legato.h"
#include "interfaces.h"

#include "location.h"

le_result_t location_get(Location *location, int timeout)
{
    le_pos_FixState_t fixState = LE_POS_STATE_NO_FIX;

    int32_t latitude = 0;
    int32_t longitude = 0;
    int32_t altitude = 0;

    int32_t horizontalAccuracy = 0;
    int32_t verticalAccuracy = 0;

    int i = 0;

    //Start location services, if they have not been started
    le_posCtrl_Request();

    //Connect this thread to the location service, if it has not been connected
    le_pos_ConnectService();

    for (i = 0; i < timeout; i++)
    {
        //Get the state of our location fix
        le_pos_GetFixState(&fixState);

        //If we're fixed
        if (fixState == LE_POS_STATE_FIX_2D || fixState == LE_POS_STATE_FIX_3D)
        {
            //Get our location
            le_pos_Get3DLocation(&latitude, &longitude, &horizontalAccuracy, &altitude, &verticalAccuracy);

            //Return the location to the caller
            location->latitude = latitude / 1000000.0;
            location->longitude = longitude / 1000000.0;
            location->altitude = altitude / 1000.0;
            location->horizontalAccuracy = horizontalAccuracy;
            location->verticalAccuracy = verticalAccuracy;

            //Print the location
            LE_INFO("Latitude: %f Longitude: %f Elevation: %f", location->latitude, location->longitude, location->altitude);

            //Return
            return LE_OK;
        }
        else
        {
            //Otherwise wait for a little bit
            sleep(1);
        }
    }

    return LE_TIMEOUT;
}
