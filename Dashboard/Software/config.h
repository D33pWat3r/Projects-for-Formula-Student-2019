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


/**
 * Display & LED Configuration
 */

#define DISPLAY_REFRESH_RATE 500 //in milliseconds
#define NEOPIXEL_REFRESH_RATE 20 //in milliseconds
#endif