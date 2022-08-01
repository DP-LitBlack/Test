#include "data_processor.h"

/**
 * @brief The interrupt handler of the sensor data. It will be called automatically when
 *        a sensor reading is received.
 * @param[in] data One sensor reading ends with "\n". You should modify this data to 
 *                 achieve your goal. Data will always be sent each time when the interrupt
 *                 is triggered. 
 */
void interrupt_handler(char *data) {
    // TO DO: You need to process the sensor data here

    /************* My Code ****************/
    int length = strlen(data);
    data[strcspn(data, "\n")] = 0;
    int data_out = atoi(data) / 2;
    snprintf(data, length, "%d\n", data_out);
    /********** End of My Code *************/

    printf("%s", data);


}
