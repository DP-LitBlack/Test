#include "data_logging.h"

static FILE *fp;

void open_log() {
    fp = fopen("log.txt","w");;
    if(fp == NULL)
    {
        printf("Error: Logging failed");   
        exit(1);             
    }
}

void log_data(char *data) {
    fprintf(fp,"%s",data);
}

void close_log() {
    fclose(fp);
}