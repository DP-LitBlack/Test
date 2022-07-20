#include <stdio.h>
#include <stdlib.h>

#include "signal_generator.h"

/**
 * @brief Read simulated signal data from a file
 * @param[in] fp A file pointer
 * @param[in] line A buffer to store the line
 * @return A line from the file, NULL for empty lines
 * @pre The buffer size should be larger than the length of the longest data
 */
char *signal_Simulator(FILE *fp, char *line) {
    size_t len = 0;
    ssize_t read;
    
    if (fp == NULL)
        exit(EXIT_FAILURE);

    if ((read = getline(&line, &len, fp)) != -1) {
        return line;
    }

    return NULL;
}