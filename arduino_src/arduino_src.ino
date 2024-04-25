#include "RTC_SAMD51.h"
#include "DateTime.h"
#include <TFT_eSPI.h>
#include "Secrets.h"

RTC_SAMD51 rtc;
TFT_eSPI tft = TFT_eSPI(); // Initialize TFT screen

void setup()
{
    rtc.begin();

    Serial.begin(115200);

    tft.init(); // Initialize TFT screen
    tft.setRotation(1); // Set screen rotation if needed

    DateTime now = DateTime(F(__DATE__), F(__TIME__));
    Serial.println("adjust time!");
    rtc.adjust(now);

    now = rtc.now();

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
    tft.print(now.hour()+2, DEC);
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