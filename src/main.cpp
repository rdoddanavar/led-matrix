// Including the required Arduino libraries
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <stdint.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Define size and output pins
#define MAX_DEVICES 4
#define CS_PIN 7

// Create a new instance of the MD_Parola class with hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Define timekeeping data
uint8_t hour24;
uint8_t hour12;
uint8_t min;
uint8_t sec;

#define AM 0
#define PM 1

char merStr[] = "AM";
uint8_t mer;

char timeStr[] = "HH:MM:SS AM";

void setup()
{

    // Intialize the object
    //myDisplay.begin();

    // Set the intensity (brightness) of the display (0-15)
    //myDisplay.setIntensity(0);

    // Clear the display
    //myDisplay.displayClear();
    //myDisplay.setTextAlignment(PA_LEFT);

    Serial.begin(9600);
    while (!Serial);  
    Serial.println("Begin");

    hour24 = 11;
    hour12 = 11;
    min    = 59;
    sec    = 50;

}

void loop()
{

    // Build time str
    snprintf(timeStr, sizeof(timeStr), "%02u:%02u:%02u %s", hour12, min, sec, merStr);
    //myDisplay.print(timeStr);

    Serial.println(timeStr);

    delay(1000);

    // Increment time
    sec++;

    if (sec >= 60)
    {
        sec = 0;
        min++;
    }

    if (min >= 60)
    {
        min = 0;
        hour24++;
    }

    if (hour24 >= 24)
    {
        hour24 = 0;
    }

    if (hour24 < 12)
    {
        mer = AM;
        merStr[0] = 'A';
        hour12 = (hour24 < 1) ? (12) : (hour24);
    }
    else // (hour24 >= 12)
    {
        mer = PM;
        merStr[0] = 'P';
        hour12 = (hour24 > 12) ? (hour24 - 12) : (hour24);
    }

}
