#include "data_processor.h"

/**
 * @brief The interrupt handler of the sensor data. It will be called automatically when
 *        a sensor reading is received.
 * @param[in] data One sensor reading ends with "\n". You should modify this data to 
 *                 achieve your goal. Data will always be sent each time when the interrupt
 *                 is triggered.
 * CAUTION: data should always be 
 */
void interrupt_handler(char *data) {
    // TO DO: You need to process the sensor data here

    /************* My Code ****************/
    char *eptr;
    double data_double;
    int length = strlen(data);
    data[strcspn(data, "\n")] = 0;
    data_double = strtod(data, &eptr);
    double data_out = data_double / 2.0;
    snprintf(data, length, "%0.4f\n", data_out);
    /********** End of My Code *************/

    printf("%s", data);


}






