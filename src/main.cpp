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
#define CS_PIN 10

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

//char timeStr[] = "HH:MM:SS AM";
char timeStr[] = "HH:MM:SS AM 0-0-0-0";

// Define input pins
#define BTN_HR_PIN   6
#define BTN_MIN_PIN  7
#define BTN_MER_PIN  8
#define BTN_MODE_PIN 9

uint8_t btnHrVal   = 0;
uint8_t btnMinVal  = 0;
uint8_t btnMerVal  = 0;
uint8_t btnModeVal = 0;

uint8_t count = 0;
bool printTime = false;

void read_buttons()
{

    btnHrVal   += !digitalRead(BTN_HR_PIN  );
    btnMinVal  += !digitalRead(BTN_MIN_PIN );
    btnMerVal  += !digitalRead(BTN_MER_PIN );
    btnModeVal += !digitalRead(BTN_MODE_PIN);

}

void reset_buttons()
{

    btnHrVal   = 0;
    btnMinVal  = 0;
    btnMerVal  = 0;
    btnModeVal = 0;

}

void set_buttons()
{

    btnHrVal   = (btnHrVal)   ? (1) : 0;
    btnMinVal  = (btnMinVal)  ? (1) : 0;
    btnMerVal  = (btnMerVal)  ? (1) : 0;
    btnModeVal = (btnModeVal) ? (1) : 0;

}

void time_keep()
{

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

    // Initialize time keeping
    hour24 = 11;
    hour12 = 11;
    min    = 59;
    sec    = 50;

    // Setup input pins
    pinMode(BTN_HR_PIN  , INPUT_PULLUP);
    pinMode(BTN_MIN_PIN , INPUT_PULLUP);
    pinMode(BTN_MER_PIN , INPUT_PULLUP);
    pinMode(BTN_MODE_PIN, INPUT_PULLUP);

}

void loop()
{

    if (printTime)
    {
        // Build time str
        snprintf(timeStr, sizeof(timeStr), "%02u:%02u:%02u %s %u-%u-%u-%u",
        hour12, min, sec, merStr, btnHrVal, btnMinVal, btnMerVal, btnModeVal);
        //myDisplay.print(timeStr);
        Serial.println(timeStr);
        printTime = false;
        reset_buttons();
    }

    delay(100); // Run at 10 Hz
    count++;

    read_buttons();

    if (count >= 10)
    {
        time_keep();
        count = 0;
        printTime = true;
        set_buttons();
    }

}
