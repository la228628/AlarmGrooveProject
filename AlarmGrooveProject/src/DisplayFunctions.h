// DisplayFunctions.h

#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Extern declaration to use the display object
extern Adafruit_ILI9341 tft;

void unSelectAll();
void selectMenuIndex();
void updateMainMenu();
void showIpInformations( const char* ip, const char* mask, const char* gateway, const char* ssid);
void showWelcomeScreen();

void showFatalErrorScreen();
void showWifiConnectionWaitScreen();
void showWifiConnectionSuccessScreen(const char* ip);



void showRestartConfirmActionScreen();


void showMusicOnSD(int musicName);
void showMusicChoiceValidationScreen(int music);

void showAlarmClockMainScreen(int choosenMusic, int musicVolume,float temperature, const char *weather, const char* lat, const char* lon);

void resetDisplay();

#endif // DISPLAYFUNCTIONS_H
