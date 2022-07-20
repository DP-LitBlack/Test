#include <stdio.h>
#include <stdlib.h>

/**
 * @brief The interrupt handler of the sensor data. It will be called automatically when
 *        a sensor reading is received.
 * @param[in] data One sensor reading
 */
void interrupt_Handler(char *data) {
    // TO DO: You need to process the sensor data here
    printf("%s", data);
}
