/*
* File name: gpioCore.h
* Code author: Ramana R (github@Rr42)
* Code version: v1.0
* Application: GPIO test driver module
* Description: 
*   This code provides definitions for the core GPIO functionality required by the GPIO test driver module.
* License:
*   Copyright (C) 2019  Ramana R (github@Rr42)
*   
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*   
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*   
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
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