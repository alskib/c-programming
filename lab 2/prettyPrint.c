#include <math.h>

void prettyPrint(char string[], float value) {
    // Insert commas and dollar sign where appropriate for values (only valid for < 1 million)
    if (value >= 1000) {
        sprintf(string, "$%d,%03d.%02.0f ", (int)value/1000, (int)value % 1000, (value-floor(value))*100);
    } else {
        sprintf(string, "$%d.%02.0f ", (int)value % 1000, (value-floor(value))*100);
    }
}
