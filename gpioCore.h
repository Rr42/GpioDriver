/*
* File name: gpioCore.h
* Code author: Ramana R (github@Rr42)
* Code version: v1.0
* Application: GPIO test driver
* Notes: 
* 	This code provides declarations for the core GPIO functionality required by the GPIO test driver.
*/

/* Includes */
#include <linux/gpio.h>
// #include "/usr/include/wiringPi.h"

/* Pin number for indicator LED */
#define INDICATOR_LED 21

/* Possible GPIO pin states */
#define LOW 0
#define HIGH 1

/* Functions */
int gpioInit(void);
int gpioSetSignalL(void);
int gpioSetSignalH(void);
int gpioExit(void);
