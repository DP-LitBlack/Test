#include <stdio.h>
#include <stdlib.h>

#include "signal_generator.h"

int IRQ_Handler() {
    return rand();
}