/*                       IDE driver for FOSKRNL                   */
/*                       Figa Systems 2020-2023                   */
/*                       All rights reserved Fsys                 */
#include <init.h>
#include <io.h>
int drive_list = 0;
void initial_code() {
    drive_list = open_list();
}

int open_list() {
   char* devices[] = {
      “/dev/", 
      "/dev/cdrom0",
  “/dev/cdrom”,
       };

  int cdrom_count[3] = {0, 0, 0};

 
