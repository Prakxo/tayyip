#include "tayyip.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

static FILE* ini; 

#define MAX_LINE 255

#define IS_VALID_DATA_DELIMITER(c) (c == ':' || c == '=')

#define ARRAY_COUNT(arr) (int)(sizeof(arr) / sizeof(arr[0]))

static INI_c* current_ini;

static void fillPrim(void* p, int value){
    char* pc = p;
    int i;

    for(i = 0; i < ARRAY_COUNT(pc); i++){
        pc[i] = value;
    }
}


static int strlen_null(char* s){
    char* p = s;
    int len = 0;

    int i;

    for(i = 0; i < strlen(p); i++){
        if(p[i] != '\0'){
            len++;
        }
    }

    return len;
}

static char* TAYYIP_get_cur_line(FILE* file, int* linesize){
    char* line = (char*)malloc(MAX_LINE);
    fgets(line, MAX_LINE, file);

    if(*line != '\0'){

        *linesize = strlen(line);
        return line;
    }
    else{
        return NULL;
    }
}

static char* strip_whitespace(char* data){
    int len = strlen_null(data);
    char* res = (char*)malloc(len);
    int i;
    int newlen = 0;

    for(i = 0; i < len; i++){
        if(data[i] == '\0' || data[i] == '\n'){
            break;
        }
        if(data[i] != ' '){
            res[newlen] = data[i];
            newlen++;
        }
    }

    return res;
}

static int TAYYIP_get_value_num(char* s){
    int  i;
    int len = strlen(s);
    int num = 0;
    
    for(i = 0; i < len; i++){
        char c = s[i];
        if(c == ','){
            num++;
        } 
    }

    return num;
}

static int TAYYIP_parse_entry(INI_Entry_c* entry, char* unparsed_entry){

    if(unparsed_entry != NULL){
        char data[200];
        char** values;
        char* cur_value;
        int value_num;
        int i;
        int len = strlen_null(unparsed_entry);
        char c;
        int del_pos = 0;

        for(i = 0; i < len; i++){
            c = unparsed_entry[i];

            if(IS_VALID_DATA_DELIMITER(c)){
                del_pos = i+1;

                break;
            }
            else{
                data[i] = unparsed_entry[i]; 
            }
        }

        entry->data = strip_whitespace(data);

        
        entry->value_num = value_num = TAYYIP_get_value_num(unparsed_entry);

        entry->value = malloc(sizeof(char*) * entry->value_num);


        fillPrim(data,0);

        strncpy(data, unparsed_entry + (del_pos), len - del_pos);

        for(i = 0; i <= value_num; i++){
            if(i == 0){
                cur_value = strtok(data, ",");
                cur_value = strip_whitespace(cur_value);
                entry->value[i] = cur_value;
            }
            else{
                cur_value = strtok(NULL, ",");
                cur_value = strip_whitespace(cur_value);
                entry->value[i] = cur_value;
            }
        }
    }
}

static int TAYYIP_fill_entries(INI_c* ini_file){
    int i = 0;
    char* cur;
    int size;
    INI_Entry_c* entry_p = malloc(sizeof(void*));

    while(cur = TAYYIP_get_cur_line(ini, &size), cur != NULL){

        if(cur[0] != ';'){
            TAYYIP_parse_entry(entry_p, cur);
        }

        ini_file->entries[i] = *entry_p;

        entry_p++;
        i++;
    }

}

INI_c* TAYYIP_ct(const char* file){
    INI_c ini_file;

    ini_file.file = file;

    ini = fopen(ini_file.file, "r");

    if(ini == NULL){
        return NULL;
    }

    ini_file.entries = malloc(sizeof(void*));

    TAYYIP_fill_entries(&ini_file);

    current_ini = &ini_file;

    return current_ini;
}

void TAYYIP_dt(const char* file){
    if(ini != NULL){
        fclose(ini);
    }

}
