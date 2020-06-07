#ifndef CONFIG_H
#define CONFIG_H

/**
 * Hardware Configuration
 * see in the schematic layout for the Pin configuration
 */

// CAN-BUS 
#define CAN_SPI_CS_PIN 10
#define CAN_INT_PIN 2

// 7-Segment Display
#define DISPLAY_CLK 19
#define DISPLAY_DIO 18

// Neopixel LED Band
#define NEOPIXEL_PIN 4

//Input Configuration
#define BUTTON_PIN 3 //is an Interrupt Pin too
#define BUTTON_BOUNCE_TIME 200 //a Button bounce between HIGH and LOW for a specific time; this is the max. bounce time in milliseconds

//LED Output Configuration
#define LED_PIN_1 5
#define LED_PIN_2 6
#define LED_PIN_3 9

//***********************************************************************************************

/**
 * Display Configuration
 */
#define DISPLAY_REFRESH_RATE 500 //in milliseconds
#define DISPLAY_BRIGHTNESS  7 //1 - 7
#define DISPLAY_NUMBER_OF_SCREENS 2 //Number of Display screens with different Values
#define DISPLAY_DELAY_BY_SCREEN_CHANGE 1000 //time in milliseconds for show the current Display Screen Number
#define DISPLAY_NUMBER_OF_STATES 3 // delay time in milliseconds for show the different values
#define DISPLAY_DELAY_MULTIPLIER 3 // the refresh Rate of the State-Mode based of the (DISPLAY_REFRESH_RATE * DISPLAY_DELAY_MULTIPLIER)

/**
 * LED-Band Configuration
 * different Color values
 */
#define NEOPIXEL_NUMBER_OF_LEDS 14
#define NEOPIXEL_REFRESH_RATE 10 //in milliseconds
#define NEOPIXEL_BRIGHTNESS 5 //[0 - 255]; the normal ligth level if the Led Band

#define NEOPIXEL_SHIFTLIGHT_BRIGHTNESS 255 // [NEOPIXEL_BRIGHTNESS-255]; the light Level for a short flash
#define NEOPIXEL_SHIFTLIGHT_CAN 0 //turn on CAN Shift Light Indicator with 1; turn off with 0

#define NEOPIXEL_SHIFTLIGHT_CHANGE_GEAR_1 30  //x100
#define NEOPIXEL_SHIFTLIGHT_CHANGE_GEAR_2 50  //x100
#define NEOPIXEL_SHIFTLIGHT_CHANGE_GEAR_3 80  //x100
#define NEOPIXEL_SHIFTLIGHT_CHANGE_GEAR_4 100 //x100
#define NEOPIXEL_SHIFTLIGHT_RANGE 3 //x100

#define NEOPIXEL_RPM_LOW 20 //x100
#define NEOPIXEL_RPM_MIDDLE 40 //x100
#define NEOPIXEL_RPM_HIGH 60 //x100
#define NEOPIXEL_RPM_MAX 130 //x100
#define NEOPIXEL_RPM_MIN_LED 1 //the RPM View should not be empty; this Value stands for the LEDs, which show the current RPM Mode
#define NEOPIXEL_RPM_LOLD_COLOR 0
#define NEOPIXEL_RPM_LOW_BRIGHTNESS 8 // [0-NEOPIXEL_BRIGHTNESS]; the light Level for the old RPM Color



/**
 * Demo Configuration
 */
#define DEMO_CALC_SPEED 20 //in milliseconds
#define DEMO_BUTTON_NUMBER 3 //the number of short pushes to activate the Demo Mode
#define DEMO_BUTTON_MAX_DELAY 500 //the max time to push the button each to activate the Demo Mode; must be higher than the BUTTON_BOUNCE_TIME 

/**
 * Switch debug output on and off by 1 or 0
 */
#define DEBUG 0

#endif
