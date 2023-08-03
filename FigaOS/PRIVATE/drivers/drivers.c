#include "../ntos/inc/stdint.h"
#include "../ntos/inc/string.h"
#include "../ntos/inc/stdef.h"
int REGISTRED_DRIVERS = {};

void register_driver(const char *driver_name) {
    for (uint8 id; id < sizeof(REGISTRED_DRIVERS) / sizeof(REGISTRED_DRIVERS[0]); id++) {
        REGISTRED_DRIVERS[id] = *driver_name
        return id;
    }
}
void unregister_driver(const char *driver_name) {
    for(int i = 0; i < strlen(REGISTRED_DRIVERS); i++)
{
    if(REGISTRED_DRIVERS[i] == *driver_name)
    {
        for(int j = i; j < strlen(REGISTRED_DRIVERS); j ++)
        {
            REGISTRED_DRIVERS[j] = REGISTRED_DRIVERS[j+1];    
        }
        break;
    }
}

}
