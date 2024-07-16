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
void showIpInformations( const char* ip, const char* mask, const char* gateway,  char *ftpHost, const char* ssid);
void showWelcomeScreen();
void showCartMountFailed();
void showCartMountSuccess();
void showFatalErrorScreen();
void showWifiConnectionWaitScreen();
void showWifiConnectionSuccessScreen(const char* ip);
void showFetchMusicFilesNameScreen();
void showFetchMusicFilesNameSucessScreen();
void showFTPErrorsScreen();

void showMusicDownloadSuccessScreen();
void showDownloadMusicWaitingScreen();

void showRestartConfirmActionScreen();

void showMusicToDownload(const char* musicName, int musicIndex);

void showAlarmClockMainScreen();

void resetDisplay();

#endif // DISPLAYFUNCTIONS_H
