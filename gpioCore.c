/*
* File name: gpioCore.h
* Code author: Ramana R (github@Rr42)
* Code version: v1.0
* Application: GPIO test driver
* Description: 
*   This code provides definitions for the core GPIO functionality required by the GPIO test driver.
*/

#include "gpioCore.h"

int gpioInit(void)
{
    int ret = gpio_request(INDICATOR_LED, "sysfs");
    
    if (ret != 0)
        return ret;
    
    ret = gpio_direction_output(INDICATOR_LED, LOW);
    return ret;
}

int gpioSetSignalL(void)
{
    gpio_set_value(INDICATOR_LED, LOW);
    return 0;
}

int gpioSetSignalH(void)
{
    gpio_set_value(INDICATOR_LED, HIGH);
    return 0;
}

int gpioExit(void)
{
    gpio_free(INDICATOR_LED);

    return 0;
}