#include "tayyip.h"
#include "stdio.h"
#include "stdlib.h"

#define INI_ENTRY 3

int main(){
    INI_c* ini_file = TAYYIP_ct("maddi.ini");

    int i;

    for(i = 0; i < INI_ENTRY; i++){
        printf("DATA: %s\n", ini_file->entries[i].data);
        for(int j = 0; j < ini_file->entries[i].value_num+1; j++){
            printf("VALUE: %s\n", ini_file->entries[i].value[j]);
        }

    }

    TAYYIP_dt("maddi.ini");
}