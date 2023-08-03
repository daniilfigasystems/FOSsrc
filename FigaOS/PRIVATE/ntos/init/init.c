/*        Init Function for FOSKRNL      */
/*        Figa Systems 2020-2023         */
#include "PRIVATE/ntos/include/ntoskrnl.h"
char* err_code[21] = {
    "VGA_FAULT", 
    "INIT_FAULT",
    "MEMORY_ERROR",
    "IO_ERROR",
    "SUBSYSTEM_DISABLED",
    "INVALID_HANDLE",
    "INVALID_PARAMETER",
    "INVALID_ACCESS",
    "INVALID_VIDEO_MODE",
    "NO_VIDEO_MEMORY",
    "NOT_ENOUGH_MEMORY",
    "COULD_NOT_ACCESS_BLOCK",
    "REGISTER_COMPONENT_FAILED",
    "NO_REQUIRED_INSTRUCTIONS",
    "PORTS_FAILED",
    "COULD_NOT_FIND_SCREEN",
    "FILE_SYSTEM_ERROR",
    "NOT_IMPLEMENTED",
    "KERNEL_HANDLE_FAILED",
    "KERNEL_NOT_INITIALIZED",
    "DRIVER_FAULT",
};
NTAPI INIT_FAULT() {
    if (err_code[0]) {
        print_string("0X3D4");
    }
        else if (err_code[1]) {
            print_string("FxFFF");
        }
            else if (err_code[2]) {
                print_string("0x495");
            }
                else if (err_code[3]) {
                    print_string("0x101");
                }
                    else if (err_code[4]) {
                        print_string("0x16F");
                    }
                        else if (err_code[5]) {
                            print_string("0x435");
                        }
    }
    NTAPI testmain() {
        
        print_string("a");
    }



