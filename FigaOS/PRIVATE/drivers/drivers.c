#include "../ntos/include/stdint.h"
#include "../ntos/include/string.h"
#include "../ntos/include/stdef.h"
#include "serial.h"
#include "drivers.h"
int REGISTRED_DRIVERS[25] = {};
struct parametersdrivers {
    char type;
    int flags;
    char address;
    int portin;
    int portout;

};
void register_driver(const char *driver_name, const char type, int flags) {
    struct parametersdrivers *driver_name;
    *driver_name.flags = flags;
    *driver_name.type = type;
    if (*driver_name.type == "video") {
        struct parametersdrivers *driver_name+type;
        if (*driver_name.flags == 1)
        *driver_name.address = 0xA0000;
        else if (*driver_name.flags == 2)
        *driver_name.address = 0xB7000;
        else
        *driver_name.address = 0xFFFFF;
        write_com(COM1, " new driver ");
        write_com(COM1, *driver_name);
        write_com(COM1, " ");

    }
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
