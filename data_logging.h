#ifndef DATA_LOGGING_H
#define DATA_LOGGING_H

#include <stdio.h>
#include <stdlib.h>

void open_log();
void log_data(char *data);
void close_log();

#endif