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
#define NEOPIXEL_NUMBER_OF_LEDS 14

//Input Configuration
#define BUTTON_PIN 3 //is an Interrupt Pin too
#define BUTTON_BOUNCE_TIME 200 //a Button bounce between HIGH and LOW for a specific time; this is the max. bounce time in milliseconds

//Output Configuration
#define LED_PIN_1 5
#define LED_PIN_2 6
#define LED_PIN_3 9

/**
 * Display & LED Configuration
 */
#define DISPLAY_REFRESH_RATE 500 //in milliseconds
#define DISPLAY_BRIGHTNESS  7 //1 - 7
#define DISPLAY_NUMBER_OF_SCREENS 2 //Number of Display screens with different Values
#define DISPLAY_DELAY_BY_SCREEN_CHANGE 1000 //time in milliseconds for show the current Display Screen Number

#define NEOPIXEL_REFRESH_RATE 20 //in milliseconds
#define NEOPIXEL_BRIGHTNESS 20 //0 - 255

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
