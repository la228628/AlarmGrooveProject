// DisplayFunctions.cpp

#include "DisplayFunctions.h"
#include "MenuIndexReferences.h"
#include "RemoteTouch.h"

extern int mainMenuIndex;

void unSelectAll() {
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

void selectMenuIndex() {
    switch (mainMenuIndex) {
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

void updateMainMenu() {
    unSelectAll();
    selectMenuIndex();
}

void showIpInformations() {
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("IP Address: ");
    tft.setCursor(10, 30);
    tft.println("Not set");
    tft.setCursor(10, 50);
    tft.println("Subnet Mask: ");
    tft.setCursor(10, 70);
    tft.println("NOT SET");
    tft.setCursor(10, 90);
    tft.println("Gateway: ");
    tft.setCursor(10, 110);
    tft.println("Not set");
    tft.setCursor(10, 130);
    tft.println("FTP SERVER: ");
    tft.setCursor(10, 150);
    tft.println("NOT SET");
    delay(5000);
    tft.fillScreen(ILI9341_BLACK);
    updateMainMenu();
}


void showWelcomeScreen(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(3);

  tft.setTextSize(3);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(40, 80);
  tft.println("WELCOME TO THE");
  tft.setCursor(40, 120);
  tft.println(" ALARM GROOVE");
    
}
void showCartMountFailed(){
    tft.fillScreen(ILI9341_RED);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Card Mount Failed. Please check the card and restart the device.");

}
void showCartMountSuccess(){
    tft.fillScreen(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Card Mount Success");

}

void showWifiConnectionWaitScreen(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Connecting to WiFi");
    tft.setCursor(10, 30);
    tft.println("Please wait...");
}

void showWifiConnectionSuccessScreen(const char* ip){
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


void showMusicToDownload(const char* musicName, int musicIndex){
            tft.fillScreen(ILI9341_BLACK);

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



void resetDisplay(){
    tft.fillScreen(ILI9341_BLACK);
}
