// DisplayFunctions.cpp

#include "DisplayFunctions.h"
#include "MenuIndexReferences.h"
#include "RemoteTouch.h"

extern int mainMenuIndex;
void resetDisplay()
{
    tft.fillScreen(ILI9341_BLACK);
}
void unSelectAll()
{
    tft.fillRect(0, 0, 320, 40, ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println(SETMUSICTEXT);
    tft.drawRect(0, 0, 320, 40, ILI9341_WHITE);

    tft.fillRect(0, 40, 320, 40, ILI9341_BLACK);
    tft.setCursor(10, 50);
    tft.println(SETALARMTIMETEXT);
    tft.drawRect(0, 40, 320, 40, ILI9341_WHITE);

    tft.fillRect(0, 80, 320, 40, ILI9341_BLACK);
    tft.setCursor(10, 90);
    tft.println(SETVOLUMETEXT);
    tft.drawRect(0, 80, 320, 40, ILI9341_WHITE);

    tft.fillRect(0, 120, 320, 40, ILI9341_BLACK);
    tft.setCursor(10, 130);
    tft.println(GETIPINFOTEXT);
    tft.drawRect(0, 120, 320, 40, ILI9341_WHITE);

    tft.fillRect(0, 160, 320, 40, ILI9341_BLACK);
    tft.setCursor(10, 170);
    tft.println(SERIALCOMTEXT);
    tft.drawRect(0, 160, 320, 40, ILI9341_WHITE);
}

void selectMenuIndex()
{
    switch (mainMenuIndex)
    {
    case MAINMENUSETMUSICINDEX:
        tft.fillRect(0, 0, 320, 40, ILI9341_BLUE);
        tft.setCursor(10, 10);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.println(SETMUSICTEXT);
        break;
    case MAINMENUSETALARMTIMEINDEX:
        tft.fillRect(0, 40, 320, 40, ILI9341_BLUE);
        tft.setCursor(10, 50);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.println(SETALARMTIMETEXT);
        break;
    case MAINMENUSETVOLUME:
        tft.fillRect(0, 80, 320, 40, ILI9341_BLUE);
        tft.setCursor(10, 90);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.println(SETVOLUMETEXT);
        break;
    case MAINMENUGETIPINFOSINDEX:
        tft.fillRect(0, 120, 320, 40, ILI9341_BLUE);
        tft.setCursor(10, 130);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.println(GETIPINFOTEXT);
        break;

    case MAINSERIALCOMMENUINDEX:
        tft.fillRect(0, 160, 320, 40, ILI9341_BLUE);
        tft.setCursor(10, 170);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.println(SERIALCOMTEXT);
        break;
    default:
        tft.println(mainMenuIndex);
        break;
    }
}

void updateMainMenu()
{
    unSelectAll();
    selectMenuIndex();
}

void showIpInformations(const char *ip, const char *mask, const char *gateway, const char *ssid)
{
    tft.fillScreen(ILI9341_BLACK);

    // Set common text properties
    tft.setTextSize(2);

    // Display IP Address
    tft.setTextColor(ILI9341_CYAN); // Label color
    tft.setCursor(10, 10);
    tft.println("IP Address: ");
    tft.setTextColor(ILI9341_WHITE); // Value color
    tft.setCursor(10, 30);
    tft.println(ip);

    // Display Subnet Mask
    tft.setTextColor(ILI9341_CYAN); // Label color
    tft.setCursor(10, 50);
    tft.println("Subnet Mask: ");
    tft.setTextColor(ILI9341_WHITE); // Value color
    tft.setCursor(10, 70);
    tft.println(mask);

    // Display Gateway
    tft.setTextColor(ILI9341_CYAN); // Label color
    tft.setCursor(10, 90);
    tft.println("Gateway: ");
    tft.setTextColor(ILI9341_WHITE); // Value color
    tft.setCursor(10, 110);
    tft.println(gateway);

    // Display SSID
    tft.setTextColor(ILI9341_CYAN); // Label color
    tft.setCursor(10, 130);
    tft.println("SSID: ");
    tft.setTextColor(ILI9341_WHITE); // Value color
    tft.setCursor(10, 150);
    tft.println(ssid);

    tft.setTextSize(1);
    tft.setCursor(10, 220);
    tft.setTextColor(ILI9341_ORANGE);
    tft.println("Press |<< to return to the main menu");

    // Optional: Draw a border around the text area
    tft.drawRect(5, 5, tft.width() - 10, tft.height() - 10, ILI9341_WHITE);
}

void showWelcomeScreen()
{

    tft.fillScreen(ILI9341_BLACK);
    tft.setRotation(3);

    static const unsigned char PROGMEM image_paint_0_bits[] = {0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x10, 0x60, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00, 0x20, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x40, 0x03, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0xc0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x30, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x38, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00};
    static const unsigned char PROGMEM image_paint_1_bits[] = {0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x18, 0x20, 0x00, 0x00, 0x00, 0x00, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x60, 0x10, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x0c, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x04, 0x00, 0x00, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x01, 0x80, 0x00, 0x07, 0x80, 0x00, 0x00, 0xe0, 0x00, 0x38, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0x00, 0x00};
    static const unsigned char PROGMEM image_paint_2_bits[] = {0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0x81, 0xc0, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x60, 0x00, 0x00, 0x00, 0x30, 0x00, 0x10, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x0c, 0x00, 0x00, 0x01, 0x80, 0x00, 0x04, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x00, 0x00, 0x40, 0x00, 0x30, 0x00, 0x00, 0x00, 0x20, 0x00, 0x60, 0x00, 0x00, 0x00, 0x18, 0x00, 0x40, 0x00, 0x00, 0x00, 0x08, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10};
    static const unsigned char PROGMEM image_paint_3_bits[] = {0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x38, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 0x70, 0x00, 0x00, 0x02, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x03, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const unsigned char PROGMEM image_music_bits[] = {0x00, 0x7c, 0x0f, 0x84, 0x08, 0x04, 0x08, 0x7c, 0x0f, 0xc4, 0x08, 0x04, 0x08, 0x04, 0x08, 0x04, 0x08, 0x04, 0x08, 0x04, 0x08, 0x38, 0x70, 0x44, 0x88, 0x44, 0x88, 0x38, 0x70, 0x00, 0x00, 0x00};
    tft.drawCircle(156, 119, 103, 0xFFFF);
    tft.drawBitmap(200, 187, image_paint_0_bits, 45, 37, 0xFFFF);
    tft.drawBitmap(67, 187, image_paint_1_bits, 45, 37, 0xFFFF);
    tft.drawBitmap(198, 13, image_paint_2_bits, 44, 49, 0xFFFF);
    tft.drawBitmap(68, 14, image_paint_3_bits, 44, 49, 0xFFFF);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(2);
    tft.setCursor(119, 87);
    tft.print("TO THE");
    tft.setTextSize(3);
    tft.setCursor(95, 46);
    tft.print("WELCOME");
    tft.setCursor(111, 120);
    tft.print("ALARM");
    tft.setCursor(106, 163);
    tft.print("GROOVE");
    tft.drawBitmap(281, 111, image_music_bits, 14, 16, 0xFFFF);
    tft.drawBitmap(263, 62, image_music_bits, 14, 16, 0xFFFF);
    tft.drawBitmap(261, 184, image_music_bits, 14, 16, 0xFFFF);
    tft.drawBitmap(24, 130, image_music_bits, 14, 16, 0xFFFF);
    tft.drawBitmap(27, 41, image_music_bits, 14, 16, 0xFFFF);
    tft.drawBitmap(18, 177, image_music_bits, 14, 16, 0xFFFF);
}

void showWifiConnectionWaitScreen()
{
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Connecting to WiFi");
    tft.setCursor(10, 30);
    tft.println("Please wait...");
    tft.setCursor(10, 50);
    tft.println("This may take a while");
    tft.setCursor(10, 70);
    tft.println("If it takes too long");
    tft.setCursor(10, 90);
    tft.println("Press PAUSE to skip the process");
}

void showWifiConnectionSuccessScreen(const char *ip)
{
    tft.fillScreen(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Connected to WiFi");
    tft.setCursor(10, 30);
    tft.println("IP Address: ");
    tft.setCursor(10, 50);
    tft.println(ip);
}

void showMusicOnSD(int musicIndex)
{
    resetDisplay();

    tft.drawRect(5, 5, 310, 50, ILI9341_WHITE);
    tft.fillRect(5, 5, 310, 50, ILI9341_DARKGREY);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 20);
    tft.println("Select the music you want to set for alarm");

    tft.drawLine(5, 60, 315, 60, ILI9341_WHITE);

    tft.setTextSize(1);
    tft.setCursor(10, 70);
    tft.println("Press PAUSE to confirm");

    tft.setCursor(10, 90);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Tack number : ");
    tft.print(musicIndex);

    tft.setCursor(10, 110);
    tft.setTextColor(ILI9341_ORANGE);
    tft.println("Press 1 to play the music/ stop the music");

    tft.setCursor(10, 130);
    tft.setTextColor(ILI9341_ORANGE);
    tft.println("Press |<< to go back to the main menu");
}

void showFatalErrorScreen()
{
    tft.fillScreen(ILI9341_RED);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Fatal Error Occured because of the SD Card");
    tft.setCursor(10, 60);
    tft.println("Please check the card and restart the device.");
}

void showRestartConfirmActionScreen()
{
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Do you want to restart the device?");
    tft.setCursor(10, 50);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Press PAUSE to confirm");
    tft.setCursor(10, 90);
    tft.setTextColor(ILI9341_ORANGE);
    tft.println("Press |<< to cancel");
}
void showMusicChoiceValidationScreen(int music)
{
    tft.fillScreen(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("The alarm music is now :");
    tft.setCursor(10, 70);
    tft.print("Track ");
    tft.print(music);
}
void showAlarmClockMainScreen(int choosenMusic, int musicVolume, float temperature, const char *weather, String lat, String lon, int hour, int minute, int alarmH, int alarmM)
{
    resetDisplay();
    static const unsigned char PROGMEM image_music_play_button_bits[] = {0x07, 0xc0, 0x18, 0x30, 0x20, 0x08, 0x40, 0x04, 0x4c, 0x04, 0x8b, 0x82, 0x88, 0x62, 0x88, 0x1a, 0x88, 0x62, 0x8b, 0x82, 0x4c, 0x04, 0x40, 0x04, 0x20, 0x08, 0x18, 0x30, 0x07, 0xc0};
    static const unsigned char PROGMEM image_weather_temperature_bits[] = {0x1c, 0x00, 0x22, 0x02, 0x2b, 0x05, 0x2a, 0x02, 0x2b, 0x38, 0x2a, 0x60, 0x2b, 0x40, 0x2a, 0x40, 0x2a, 0x60, 0x49, 0x38, 0x9c, 0x80, 0xae, 0x80, 0xbe, 0x80, 0x9c, 0x80, 0x41, 0x00, 0x3e, 0x00};
    static const unsigned char PROGMEM image_volume_loud_bits[] = {0x01, 0xc1, 0x00, 0x02, 0x40, 0x80, 0x04, 0x44, 0x40, 0x08, 0x42, 0x20, 0xf0, 0x51, 0x20, 0x80, 0x49, 0x10, 0x80, 0x44, 0x90, 0x80, 0x44, 0x90, 0x80, 0x44, 0x90, 0x80, 0x49, 0x10, 0xf0, 0x51, 0x20, 0x08, 0x42, 0x20, 0x04, 0x44, 0x40, 0x02, 0x40, 0x80, 0x01, 0xc1, 0x00, 0x00, 0x00, 0x00};
    static const unsigned char PROGMEM image_location_map_bits[] = {0x03, 0x80, 0x04, 0x40, 0x09, 0x20, 0x12, 0x90, 0x12, 0x90, 0x11, 0x10, 0x08, 0x20, 0x04, 0x40, 0x04, 0x40, 0x1a, 0xb0, 0x21, 0x08, 0x21, 0x08, 0x40, 0x04, 0x40, 0x04, 0x9c, 0x72, 0xe3, 0x8e};
    static const unsigned char PROGMEM image_clock_alarm_bits[] = {0x79, 0x3c, 0xb3, 0x9a, 0xed, 0x6e, 0xd0, 0x16, 0xa0, 0x0a, 0x41, 0x04, 0x41, 0x04, 0x81, 0x02, 0xc1, 0x06, 0x82, 0x02, 0x44, 0x04, 0x48, 0x04, 0x20, 0x08, 0x10, 0x10, 0x2d, 0x68, 0x43, 0x84};
    tft.drawCircle(156, 127, 67, 0xFFFF);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(3);
    tft.setCursor(149, 111);
    tft.print(":");
    tft.setCursor(106, 111);
    if (hour < 10)
    {
        tft.print("0");
        tft.print(hour);
    }
    else
    {

        tft.print(hour);
    }
    tft.setCursor(174, 111);
    if (minute < 10)
    {
        tft.print("0");
        tft.print(minute);
    }
    else
    {
        tft.print(minute);
    }
    tft.drawBitmap(5, 196, image_music_play_button_bits, 15, 15, 0xFFFF);
    tft.setTextSize(1);
    tft.setCursor(28, 199);
    tft.print("TRACK");
    tft.drawBitmap(206, 8, image_weather_temperature_bits, 16, 16, 0xFFFF);
    tft.setTextSize(2);
    tft.setCursor(228, 10);
    tft.print(temperature);
    tft.drawCircle(292, 6, 2, 0xFFFF);
    tft.setCursor(300, 10);
    tft.print("C");
    tft.drawBitmap(4, 217, image_volume_loud_bits, 20, 16, 0xFFFF);
    tft.setTextSize(1);
    tft.setCursor(31, 221);
    tft.print(musicVolume);
    tft.setCursor(35, 14);
    tft.print("Lat: ");
    tft.drawBitmap(10, 9, image_location_map_bits, 15, 16, 0xFFFF);
    tft.setCursor(35, 28);
    tft.print("Long: ");
    tft.setCursor(67, 14);
    tft.print(lat);
    tft.setCursor(67, 28);
    tft.print(lon);
    tft.setTextColor(0xFC00);
    tft.setCursor(145, 215);
    tft.print("PRESS PAUSE TO GO TO MENU");
    tft.setTextColor(0xFFFF);
    tft.setTextSize(2);
    tft.setCursor(10, 100);
    tft.print("ALARM");
    tft.setTextColor(0xFFFF);
    tft.setCursor(238, 100);
    tft.print("GROOVE");
    tft.setTextSize(1);
    tft.setCursor(63, 199);
    if (choosenMusic == 0)
    {
        tft.print("NOT FOUND");
    }
    else
    {
    tft.print(choosenMusic);
    }
    tft.drawBitmap(220, 160, image_clock_alarm_bits, 15, 16, 0xFFFF);
    tft.setTextSize(2);
    tft.setCursor(244, 161);
    if (alarmH < 10)
    {
        tft.print("0");
        tft.print(alarmH);
    }
    else
    {
        tft.print(alarmH);
    }
    tft.setCursor(281, 161);
    if (alarmM < 10)
    {
        tft.print("0");
        tft.print(alarmM);
    }
    else
    {
        tft.print(alarmM);
    }
    tft.setCursor(268, 160);
    tft.print(":");
    tft.setTextSize(1);
    tft.setCursor(123, 31);
    tft.print("");
    tft.setCursor(35, 42);
    tft.print(weather);
}
void showSetVolumeScreen(int vol)
{
    resetDisplay();
    tft.drawRect(180, 194, 108, 36, 0xFFFF);
    tft.drawRect(180, 158, 108, 36, 0xFFFF);
    tft.drawRect(180, 14, 108, 36, 0xFFFF);
    tft.drawRect(180, 122, 108, 36, 0xFFFF);
    tft.drawRect(180, 86, 108, 36, 0xFFFF);
    tft.drawRect(180, 50, 108, 36, 0xFFFF);

    if (vol == 30)
    {
        tft.fillRect(180, 194, 108, 36, ILI9341_GREEN);
        tft.fillRect(180, 158, 108, 36, ILI9341_GREEN);
        tft.fillRect(180, 122, 108, 36, ILI9341_ORANGE);
        tft.fillRect(180, 86, 108, 36, ILI9341_ORANGE);
        tft.fillRect(180, 50, 108, 36, ILI9341_RED);
        tft.fillRect(180, 14, 108, 36, ILI9341_RED);
    }
    else if (vol >= 25)
    {
        tft.fillRect(180, 194, 108, 36, ILI9341_GREEN);
        tft.fillRect(180, 158, 108, 36, ILI9341_GREEN);
        tft.fillRect(180, 122, 108, 36, ILI9341_ORANGE);
        tft.fillRect(180, 86, 108, 36, ILI9341_ORANGE);
        tft.fillRect(180, 50, 108, 36, ILI9341_RED);
    }
    else if (vol >= 20)
    {
        tft.fillRect(180, 194, 108, 36, ILI9341_GREEN);
        tft.fillRect(180, 158, 108, 36, ILI9341_GREEN);
        tft.fillRect(180, 122, 108, 36, ILI9341_ORANGE);
        tft.fillRect(180, 86, 108, 36, ILI9341_ORANGE);
    }

    else if (vol >= 15)
    {
        tft.fillRect(180, 194, 108, 36, ILI9341_GREEN);
        tft.fillRect(180, 158, 108, 36, ILI9341_GREEN);
        tft.fillRect(180, 122, 108, 36, ILI9341_ORANGE);
    }
    else if (vol >= 10)
    {
        tft.fillRect(180, 194, 108, 36, ILI9341_GREEN);
        tft.fillRect(180, 158, 108, 36, ILI9341_GREEN);
    }

    else if (vol >= 5)
    {
        tft.fillRect(180, 194, 108, 36, ILI9341_GREEN);
    }

    tft.setTextColor(0xFFFF);
    tft.setTextSize(2);
    tft.setCursor(5, 12);
    tft.print("SET THE VOLUME");
    tft.setCursor(54, 46);
    tft.print("WITH ");
    tft.setCursor(22, 78);
    tft.print("VOL+ & VOL-");
    tft.setCursor(3, 142);
    tft.print("VOLUME");
    tft.setCursor(95, 141);
    tft.print(vol);
    tft.setTextColor(0xFC00);
    tft.setTextSize(1);
    tft.setCursor(20, 221);
    tft.print("PRESS |<< TO CANCEL");
    tft.setTextColor(0xFFE0);
    tft.setCursor(17, 202);
    tft.print("PRESS PAUSE TO CONFIRM");
}
void modifyAlarmClockScreen(int hour, int minute , float temperature, const char *weather)
{

    tft.setTextSize(3);

    tft.setCursor(106, 111);
    tft.fillRect(106, 111, 40, 24, ILI9341_BLACK);
    if (hour < 10)
    {
        tft.print("0");
        tft.print(hour);
    }
    else
    {

        tft.print(hour);
    }
    
    tft.setCursor(174, 111);
    tft.fillRect(174, 111, 40, 24, ILI9341_BLACK);
    if (minute < 10)
    {
        tft.print("0");
        tft.print(minute);
    }
    else
    {
        tft.print(minute);
    }
    tft.fillRect(224, 6, 65, 24, ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setCursor(228, 10);
    tft.print(temperature);

    tft.fillRect(32, 41, 286, 11, ILI9341_BLACK);
    tft.setTextSize(1);
    tft.setCursor(35, 42);
    tft.print(weather);
}

void showSetAlarmTimeScreen(int hour, int minute)
{
    resetDisplay();
    tft.drawRect(5, 5, 310, 50, ILI9341_WHITE);
    tft.fillRect(5, 5, 310, 50, ILI9341_DARKGREY);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 20);
    tft.println("Set the alarm time");

    tft.drawLine(5, 60, 315, 60, ILI9341_WHITE);

    tft.setTextSize(1);
    tft.setCursor(10, 70);
    tft.println("Press PAUSE to confirm");

    tft.setCursor(10, 90);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Press UP to increase the hour");
    tft.setCursor(10, 110);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Press DOWN to decrease the hour");
    tft.setCursor(10, 130);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Press |<< to go back to the main menu");

    tft.setCursor(10, 150);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Press VOL+ to increase the minute");
    tft.setCursor(10, 170);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Press VOL- to decrease the minute");

    tft.setCursor(10, 190);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Current time : ");
    tft.setCursor(10, 210);
    tft.setTextColor(ILI9341_YELLOW);
    if (hour < 10)
    {
        tft.print("0");
        tft.print(hour);
    }
    else
    {
        tft.print(hour);
    }
    tft.print(" : ");
    if (minute < 10)
    {
        tft.print("0");
        tft.print(minute);
    }
    else
    {
        tft.print(minute);
    }
}

void showWaitForDataScreen()
{
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Waiting for data from the app");
    tft.setCursor(10, 50);
    tft.println("Please enter the informations");
    tft.setCursor(10, 90);
    tft.println("on the application and press SEND");
}

void showConfirmInfosScreen(const char *ssid, const char *password, const char *latitude, const char *longitude, const char *apiKey)
{
    resetDisplay();
    tft.drawRect(0, 160, 160, 80, 0xFFFF);
    tft.setTextSize(1);
    tft.setTextColor(0xFFFF);
    tft.setCursor(62, 7);
    tft.print("Are these informations correct ?");
    tft.drawRect(160, 160, 160, 80, 0xFFFF);
    tft.setCursor(9, 34);
    tft.print("SSID :");
    tft.setCursor(9, 90);
    tft.print("LONG :");
    tft.setCursor(9, 62);
    tft.print("LAT :");
    tft.setCursor(5, 127);
    tft.print("API KEY :");
    tft.setTextSize(2);
    tft.setCursor(25, 170);
    tft.print("PRESS |<<");
    tft.setTextColor(0x540);
    tft.setCursor(185, 203);
    tft.print("TO CONFIRM");
    tft.setTextColor(0xFAAA);
    tft.setCursor(29, 204);
    tft.print("TO RETRY");
    tft.setTextColor(0xFFFF);
    tft.setCursor(189, 169);
    tft.print("PRESS >>|");
    tft.setTextSize(1);
    tft.setCursor(58, 62);
    tft.print(latitude);
    tft.setCursor(58, 34);
    tft.print(ssid);
    tft.setCursor(58, 89);
    tft.print(longitude);
    tft.setCursor(65, 127);
    tft.print(apiKey);
}

void showEmergencyWaitScreen()
{

    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("IF YOUR REMOTE IS NOT WORKING");
    tft.setCursor(10, 50);
    tft.println("PRESS THE BUTTON ON THE DEVICE");
    tft.setCursor(10, 90);
    tft.println("TO SET THE BUTTON");
    tft.setCursor(10, 130);
    tft.println("ELSE PLEASE WAIT");
}

void showRemoteWaitingScreen( const char *text)
{
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Remote IR is waiting");
    tft.setCursor(10, 30);
    tft.println("to set button");
    tft.setCursor(10, 50);
    tft.println("Please press the button");
    tft.setCursor(10, 70);
    tft.println(text);
}

void showWifiConnectionFailedScreen()
{
    tft.fillScreen(ILI9341_RED);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Failed to connect to WiFi");
    tft.setCursor(10, 50);
    tft.println("Please check the credentials");
    tft.setCursor(10, 90);
    tft.println("and restart the device.");
}

void showNoMusicOnSD(){
    tft.fillScreen(ILI9341_RED);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("No music found on the SD card");
    tft.setCursor(10, 50);
    tft.println("Please add some music to the SD card");
    tft.setCursor(10, 90);
    tft.println("and restart the device.");
}