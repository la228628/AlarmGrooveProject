#include <stdio.h>
#include "simple_ftp_client.h"
#include "SD_card_helper.h"

const char *ssid = "WiFi-2.4-2D90";
// const char* ssid     = "raspi-webgui";
const char *password = "wws7db5j9bu4k";

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Define the pins used for the display
#define TFT_CS 15
#define TFT_RST 4
#define TFT_DC 2
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
// end of display pins

// define the codes for the remote
#include "RemoteTouch.h"

// Define the menu index references
#include "MenuIndexReferences.h"

// Create an instance of the display
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, 23, 18, TFT_RST, -1);
// The most appropriate pins for sck and mosi are 18 and 23 respectively. Or else, use 18 and 19
//  end of display instance

// Include the file that contains the display functions
#include "DisplayFunctions.h"
// It allows to have the functions in a separate file and make the main file cleaner

// Define the pin for the mp3 player state
int Player_state = 13;

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 27; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 26; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
// Note: GPIO 14 won't work on the ESP32-C3 as it causes the board to reboot.
#ifdef ARDUINO_ESP32C3_DEV
// const uint16_t kRecvPin = 10;  // 14 on a ESP32-C3 causes a boot loop.
#else  // ARDUINO_ESP32C3_DEV
const uint16_t kRecvPin = 16;
#endif // ARDUINO_ESP32C3_DEV

IRrecv irrecv(kRecvPin);

decode_results results;

int mainMenuIndex = 1;

int currentMenu = MAINMENU;

bool waitForMenuSelection()
{
  while (true)
  {
    if (irrecv.decode(&results))
    {
      if (results.value == PAUSE)
      {
        irrecv.resume();
        return true;
      }
      else if (results.value == UP)
      {
        if (mainMenuIndex > 1)
        {
          mainMenuIndex--;
        }
        else
        {
          mainMenuIndex = 5;
        }
        updateMainMenu();
        irrecv.resume();
      }
      else if (results.value == DOWN)
      {
        if (mainMenuIndex < 5)
        {
          mainMenuIndex++;
        }
        else
        {
          mainMenuIndex = 1;
        }
        updateMainMenu();
        irrecv.resume();
      }
      else
      {
        irrecv.resume();
      }
    }
    Serial.println(mainMenuIndex);
    delay(50);
  }
}

int waitForMusicDownloadIndex(String nameList[])
{
  int index = 0;
  int indexMax = -1;

  for (int i = 0; i < 255; i++)
  {
    if (nameList[i] != "")
    {
      indexMax++;
    }
  }
  showMusicToDownload(nameList[index].c_str(), index);

  while (currentMenu == DOWNLOADMUSIC)
  {
    if (irrecv.decode(&results))
    {
      if (results.value == PAUSE)
      {
        irrecv.resume();
        return index;
      }
      else if (results.value == UP)
      {
        if (index > 0)
        {
          index--;
        }
        else
        {
          index = indexMax;
        }

        showMusicToDownload(nameList[index].c_str(), index);

        irrecv.resume();
      }
      else if (results.value == DOWN)
      {
        if (index < indexMax)
        {
          index++;
        }
        else
        {
          index = 0;
        }

        showMusicToDownload(nameList[index].c_str(), index);

        irrecv.resume();
      }
      else if (results.value == LEFT)
      {
        currentMenu = MAINMENU;
        resetDisplay();
        updateMainMenu();
        return -1;
      }
      else
      {
        irrecv.resume();
      }
    }
    Serial.println(index);
    delay(50);
  }
}

bool downloadNameMusicFile()
{

  if (connectToFTPServer())
  {
    Serial.println("Connected to FTP Server");
  }
  else
  {
    Serial.println("Connection Failed");
    tft.fillScreen(ILI9341_RED);
    tft.setCursor(10, 10);
    tft.println("Failed to download namesFiles because of connection error");
    return false;
  }

  if (!loginFTPServer("esp32user", "pass"))
  {
    Serial.println("Login Failed");
    tft.fillScreen(ILI9341_RED);
    tft.setCursor(10, 10);
    tft.println("Failed to download namesFiles because of login error");
    return false;
  }
  else
  {
    Serial.println(">Loged iN");
  }

  sendFTPCommand("NOOP");
  //sendFTPCommand("TYPE I");
  sendFTPCommand("TYPE I");
  delay(200);
  sendFTPCommand("EPSV");
  parseFTPDataPort();

  if (downloadFileFromFTP("/names/names.txt", 0, "") == false)
  {
    Serial.println("File Download Failed");
    tft.fillScreen(ILI9341_RED);
    tft.setCursor(10, 10);
    tft.println("Failed to download namesFiles because of download error");
    return false;
  }
  else
  {
    Serial.println("File Downloaded");
  }
  return true;

  delay(5000);
}

void manageMusicDownloadMenu()
{
  resetDisplay();

  currentMenu = DOWNLOADMUSIC;

  int numberOfMusicFiles = 0;

  String nameList[255];
  if (getLinesFromTxtFile("/names/names.txt", nameList))
  {
    for (int i = 0; i < 255; i++)
    {
      if (nameList[i] != "")
        Serial.println(nameList[i]);
      numberOfMusicFiles++;
    }
  }
  else
  {
    Serial.println("Failed to get names from file");
  }

  tft.setTextSize(2);

  waitForMusicDownloadIndex(nameList);
}

void manageMainMenu()
{

  updateMainMenu();

  while (currentMenu == MAINMENU)
  {
    bool menuSelected = waitForMenuSelection();
    if (menuSelected == true)
    {

      switch (mainMenuIndex)
      {
      case MAINMENUGETIPINFOSINDEX:
        // setFTPHost("0.0.0.0");
        showIpInformations(WiFi.localIP().toString().c_str(), WiFi.subnetMask().toString().c_str(), WiFi.gatewayIP().toString().c_str(), getFTPHost(), WiFi.SSID().c_str());
        while (results.value != LEFT)
        {
          if (irrecv.decode(&results))
          {
            irrecv.resume();
          }
        }
        resetDisplay();
        updateMainMenu();
        break;

      case MAINMENUDOWNLOADMUSICINDEX:
        manageMusicDownloadMenu();
        break;
      case FETCHMUSICFILENAME:
        currentMenu = FETCHMUSICFILENAME;
        resetDisplay();
        break;
      case MAINMENUSETMUSICINDEX:
        currentMenu = CHOOSEMUSIC;
        resetDisplay();
        break;
      }
    }
  }
}

void manageFetchMusicFileName()
{
  resetDisplay();
  showFetchMusicFilesNameScreen();

  if (downloadNameMusicFile())
  {
    showFetchMusicFilesNameSucessScreen();
  }
  else
  {
    showFTPErrorsScreen();
  }
  disconnectFromFTPServer();
  delay(3000);
  currentMenu = MAINMENU;
  resetDisplay();
  updateMainMenu();
}

void manageChooseMusicMenu()
{
  char *musicOnSD[255];
  int numberOfMusicFiles = getFilesFromDir("/music", 0, musicOnSD);


  if( numberOfMusicFiles == -1){
    currentMenu = MAINMENU;
    return;
  }


  Serial.println("Ready to display music files: ");
  Serial.print(numberOfMusicFiles);
  
  
  for(int i = 0; i < numberOfMusicFiles; i++)
  {
    tft.setCursor(10, 10 + i * 20);
    tft.println(musicOnSD[i]);
  }
  Serial.println("End of Ready to display music files");
  delay(5000);
  currentMenu = MAINMENU;
  
}

void setup()
{

  Serial.begin(115200);
  Serial2.begin(115200);

  irrecv.enableIRIn(); // Start the receiver
  while (!Serial)      // Wait for the serial connection to be establised.
    delay(100);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);

  tft.begin();
  tft.setFont();
  showWelcomeScreen();
  delay(1000);

  tft.fillScreen(ILI9341_BLACK);

  if (!SD_Initialize())
  {
    Serial.println("Card Mount Failed");
    showCartMountFailed();
    delay(1000);
    currentMenu = FATALERROR;
    return;
  }
  else
  {
    showCartMountSuccess();
  }

  delay(1000);

  WiFi.begin(ssid, password);

  showWifiConnectionWaitScreen();
  while (WiFi.status() != WL_CONNECTED)
  {
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  showWifiConnectionSuccessScreen(WiFi.localIP().toString().c_str());

  delay(1000);
  resetDisplay();
  updateMainMenu();

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  /*


    int musicIndex = 2;

    String pathMusicFull = "/music/" + nameList[musicIndex];

    const char *pathMusicFullToChar = pathMusicFull.c_str();

    const char *pathMusicName = nameList[2].c_str();

    Serial.println(pathMusicName);







    if (connectToFTPServer())
    {
      Serial.println("Connected to FTP Server");
    }
    else
    {
      Serial.println("Connection Failed");
    }

    if (!loginFTPServer("esp32user", "pass"))
    {
      Serial.println("Login Failed");
    }
    else
    {
      Serial.println(">Loged iN");
    }

    sendFTPCommand("NOOP");
    sendFTPCommand("TYPE I");
    sendFTPCommand("TYPE I");
    delay(200);
    sendFTPCommand("EPSV");
    parseFTPDataPort();

    if (downloadFileFromFTP(pathMusicFullToChar,musicIndex, pathMusicName) == false)
    {
      Serial.println("File Download Failed");
    }
    else
    {
      Serial.println("File Downloaded");
    }

    delay(5000);

    if (disconnectFromFTPServer())
    {
      Serial.println("Disconnected");
    }
    else
    {
      Serial.println("Disconnection Failed");
    }

    while (disconnectFromFTPServer() == false)
    {

      delay(150);
      Serial.println("Disconnection Failed, trying again...");
    }

    */
}

void loop()
{

  // put your main code here, to run repeatedly:

  if (currentMenu == FATALERROR)
  {
    showFatalErrorScreen();
    // We need to stop the loop here
    while (true)
    {
    }
  }

  switch (currentMenu)
  {
  case DOWNLOADMUSIC:
    manageMusicDownloadMenu();
    break;
  case MAINMENU:
    manageMainMenu();
    break;
  case FETCHMUSICFILENAME:
    manageFetchMusicFileName();
    break;
  case CHOOSEMUSIC:
    manageChooseMusicMenu();
    break;
  }
}
