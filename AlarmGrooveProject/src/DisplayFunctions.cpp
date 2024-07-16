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
    tft.println(DOWNLOADMUSICTEXT);
    tft.drawRect(0, 80, 320, 40, ILI9341_WHITE);

    tft.fillRect(0, 120, 320, 40, ILI9341_BLACK);
    tft.setCursor(10, 130);
    tft.println(GETIPINFOTEXT);
    tft.drawRect(0, 120, 320, 40, ILI9341_WHITE);

    tft.fillRect(0, 160, 320, 40, ILI9341_BLACK);
    tft.setCursor(10, 170);
    tft.println(FETCHMUSICFILENAMETEXT);
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
    case MAINMENUDOWNLOADMUSICINDEX:
        tft.fillRect(0, 80, 320, 40, ILI9341_BLUE);
        tft.setCursor(10, 90);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.println(DOWNLOADMUSICTEXT);
        break;
    case MAINMENUGETIPINFOSINDEX:
        tft.fillRect(0, 120, 320, 40, ILI9341_BLUE);
        tft.setCursor(10, 130);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.println(GETIPINFOTEXT);
        break;

    case FETCHMUSICFILENAMEMENUINDEX:
        tft.fillRect(0, 160, 320, 40, ILI9341_BLUE);
        tft.setCursor(10, 170);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.println(FETCHMUSICFILENAMETEXT);
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

void showIpInformations(const char *ip, const char *mask, const char *gateway, char *ftpHost, const char *ssid)
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

    // Display FTP Server
    tft.setTextColor(ILI9341_CYAN); // Label color
    tft.setCursor(10, 130);
    tft.println("FTP SERVER: ");
    tft.setTextColor(ILI9341_WHITE); // Value color
    tft.setCursor(10, 150);
    tft.println(ftpHost);

    // Display SSID
    tft.setTextColor(ILI9341_CYAN); // Label color
    tft.setCursor(10, 170);
    tft.println("SSID: ");
    tft.setTextColor(ILI9341_WHITE); // Value color
    tft.setCursor(10, 190);
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
void showCartMountFailed()
{
    tft.fillScreen(ILI9341_RED);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Card Mount Failed. Please check the card and restart the device.");
}
void showCartMountSuccess()
{
    tft.fillScreen(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Card Mount Success");
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

void showMusicToDownload(const char *musicName, int musicIndex)
{
    resetDisplay();

    tft.drawRect(5, 5, 310, 50, ILI9341_WHITE);
    tft.fillRect(5, 5, 310, 50, ILI9341_DARKGREY);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 20);
    tft.println("Select the music you want       to download");

    tft.drawLine(5, 60, 315, 60, ILI9341_WHITE);

    tft.setTextSize(1);
    tft.setCursor(10, 70);
    tft.println("Press PAUSE to confirm");

    tft.setCursor(10, 90);
    tft.setTextColor(ILI9341_YELLOW);
    tft.print(musicIndex);
    tft.print(" - ");
    tft.println(musicName);

    tft.setCursor(10, 110);
    tft.setTextColor(ILI9341_ORANGE);
    tft.println("Press |<< to go back to the main menu");
}

void showMusicOnSD(const char *musicName){
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
    tft.println(musicName);

    tft.setCursor(10, 110);
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

void showFetchMusicFilesNameScreen()
{
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Fetching music files name from the server");
    tft.setCursor(10, 50);
    tft.println("Please wait...");
}

void showFTPErrorsScreen()
{
    tft.fillScreen(ILI9341_RED);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("FTP Error Occured");
    tft.setCursor(10, 30);
    tft.println("Please check the FTP server and restart the device.");
}

void showFetchMusicFilesNameSucessScreen(){
    tft.fillScreen(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Music files name fetched successfully");
}
void showMusicDownloadSuccessScreen(){
    tft.fillScreen(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Music downloaded successfully");
}
void showDownloadMusicWaitingScreen(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Downloading music");
    tft.setCursor(10, 30);
    tft.println("Please wait...");
    tft.setCursor(10, 50);
    tft.println("This may take a while");
    tft.setCursor(10, 70);
    tft.println("Please do not turn off the device");
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
void showMusicChoiceValidationScreen(const char *musicName){
    tft.fillScreen(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("The alarm music is now :");
    tft.setCursor(10, 70);
    tft.println(musicName);
}
void showAlarmClockMainScreen(char *choosenMusic){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Alarm Clock");
    tft.setCursor(10, 50);
    tft.println("This feature is not implemented yet");
    tft.setCursor(10, 90);
    tft.println("Press PAUSE to go to the main menu");
    tft.setCursor(10,130);
    tft.println("Music :" );
    tft.print(choosenMusic);
}