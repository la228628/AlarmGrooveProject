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
void showSetVolumeScreen(int vol);



void showRestartConfirmActionScreen();


void showMusicOnSD(int musicName);
void showMusicChoiceValidationScreen(int music);

void showAlarmClockMainScreen(int choosenMusic, int musicVolume,float temperature, const char *weather, String lat, String lon, int hour, int minute, int alarmH, int alarmM);
void modifyAlarmClockScreen(int hour, int minute, float temperature, const char *weather);

void showSetAlarmTimeScreen(int hour, int minute);

void showWaitForDataScreen();
void showConfirmInfosScreen(const char* ssid, const char* password, const char* latitude, const char* longitude, const char* apiKey);
void resetDisplay();

void showEmergencyWaitScreen();

void showRemoteWaitingScreen( const char *text);

void showWifiConnectionFailedScreen();

void showNoMusicOnSD();

#endif // DISPLAYFUNCTIONS_H
