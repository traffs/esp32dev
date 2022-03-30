#include <WiFi.h>
#include "time.h"

const char *ntpServer = "pool.ntp.org";

class TimeGetter
{
public:
    int timezone;
    int daylightOffset;
    TimeGetter(int timezone)
    {
        // WiFiUDP ntpUDP;
        configTime(timezone * 3600, daylightOffset, ntpServer);
        //  configTime(0, 0, ntpServer);
        TimeStamp();

        // timeClient.begin();
        // timeClient.setTimeOffset(timezone * 3600);
    }
    // String TimeStamp()
    unsigned long TimeStamp()
    {
        // struct tm timeinfo;
        time_t now;
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo))
        {
            // Serial.println("Failed to obtain time");
            return (0);
        }
        time(&now);
        unsigned long epochTime = now;
        return now;
    }
};
