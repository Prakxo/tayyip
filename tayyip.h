#ifndef TAYYIP_H
#define TAYYIP_H

#include "types.h"

/* TERRIBLE AT (YUCKY YEAH) INI PARSING*/

typedef struct ini_entry_s {
     char* data;
     char** value;
    int value_num;
} INI_Entry_c;

typedef struct ini_s {
    const char* file;
    INI_Entry_c* entries;
} INI_c;


INI_c* TAYYIP_ct(const char* file);

void TAYYIP_dt(const char* file);
 

#endif