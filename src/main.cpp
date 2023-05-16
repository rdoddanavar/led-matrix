// Including the required Arduino libraries
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 4
#define CS_PIN 7

// Create a new instance of the MD_Parola class with hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int hour;
int min;
int sec;

int  mer;
char merStr[2];
#define AM 0
#define PM 1

// 8 characters: "HH:MM AM"
char timeStr[8];

void setup()
{

    // Intialize the object
    //myDisplay.begin();

    // Set the intensity (brightness) of the display (0-15)
    //myDisplay.setIntensity(0);

    // Clear the display
    //myDisplay.displayClear();
    //myDisplay.setTextAlignment(PA_LEFT);

    // Initialize time
    hour = 12;
    min  = 0;
    sec  = 0;

    mer = AM;
    merStr[0] = 'A';
    merStr[1] = 'M';

    Serial.begin(9600);
    while (!Serial);  
    Serial.println("Begin");

}

void loop()
{

    // Build time str
    snprintf(timeStr, sizeof(timeStr), "%d:%d %s", hour, min, merStr);
    //myDisplay.print(timeStr);

    Serial.println("test");

    delay(1000);

    // Increment time
    sec++;

    if (!(sec % 60))
    {
        sec = 0;
        min++;
    }

    if (!(min % 60))
    {
        min = 0;
        hour++;
    }

    if (!(hour % 12))
    {
        hour = 12;
        mer++;
    }

    if (!(mer % 2))
    {
        mer = 0;
        merStr[0] = 'A';
    }
    else
    {
        merStr[0] = 'P';
    }

}
