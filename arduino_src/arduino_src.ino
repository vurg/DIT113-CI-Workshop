/******************************************************************************
 * Title:    CI/CD Workshop for DIT113 with the Wio Terminal
 * Author:   Nasit Vurgun (Nas)
 * Date:     2024-04-26
 * Purpose:  This workshop aims to teach students the fundamental concepts of
 *           Continuous Integration (CI) and Continuous Deployment (CD). It uses 
 *           GitLab's CI/CD environment where students will implement changes to
 *           fix a broken CI pipeline, learn about environment variables, and 
 *           deploy their code to production on a target Wio Terminal device. 
 ******************************************************************************/

#include "RTC_SAMD51.h"
#include "DateTime.h"
#include <TFT_eSPI.h>
#include "Secrets.h"

#define TIME_ZONE_OFFSET 2 // Gothenburg is UTC+2 currently

RTC_SAMD51 rtc; // initialize RTC clock object
TFT_eSPI tft = TFT_eSPI(); // Initialize TFT screen

void setup()
{
    rtc.begin(); // Begin RTC clock

    Serial.begin(115200); // Begin Serial communication

    tft.init(); // Initialize TFT screen
    tft.setRotation(1); // Set screen rotation if needed

    DateTime now = DateTime(F(__DATE__), F(__TIME__)); // Create DateTime object
    Serial.println("adjust time!");
    rtc.adjust(now); // set initial time

    now = rtc.now(); // get current time

    // Clear screen
    tft.fillScreen(TFT_BLACK);

    // Print date and time on TFT screen
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 0);
    tft.print(now.year(), DEC);
    tft.print('/');
    tft.print(now.month(), DEC);
    tft.print('/');
    tft.print(now.day(), DEC);
    tft.print(" ");
    tft.print(now.hour() + TIME_ZONE_OFFSET, DEC);
    tft.print(':');
    tft.print(now.minute(), DEC);
    tft.print(':');
    tft.print(now.second(), DEC);

    // Print super secret message from author
    tft.setTextFont(1);
    tft.setCursor(10, 100);
    tft.print(MY_MESSAGE);
}

void loop()
{
    // Your loop code here, if any
}