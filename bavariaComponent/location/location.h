
#ifndef LOCATION_SERVICE_H
#define LOCATION_SERVICE_H

typedef struct
{
    double latitude;
    double longitude;
    double altitude;

    int32_t horizontalAccuracy;
    int32_t verticalAccuracy;
} Location;

le_result_t location_get(Location *location, int timeout);

#endif //LOCATION_SERVICE_H
