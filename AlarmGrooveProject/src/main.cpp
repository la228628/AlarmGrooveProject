#include <stdio.h>
#include <Wifi.h>

char *ssidToConnect = "WiFi-2.4-2D90";
char *passwordToConnect = "wws7db5j9bu4k";

const char *ssid = ssidToConnect;
// const char* ssid     = "raspi-webgui";
const char *password = passwordToConnect;

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

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
#define DFPSerial Serial1
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

int currentMenu = ALARMCLOCKMAINSCREEN;

int choosenMusic = 1;
int musicVolume = 2;
int folderCount = 0;



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
      else if (results.value == POWER)
      {
        currentMenu = RESTARTCONFIRMACTION;
        return false;
      }
      else if (results.value == LEFT)
      {
        currentMenu = ALARMCLOCKMAINSCREEN;
        return false;
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

int waitForMusicToSet(int numberOfMusicFiles)
{

  int index = 1;
  int indexmax = numberOfMusicFiles;

  showMusicOnSD(index);

  while (currentMenu == CHOOSEMUSIC)
  {

    if (irrecv.decode(&results))
    {

      if (results.value == PAUSE)
      {
        player.stop();
        irrecv.resume();
        return index;
      }
      else if (results.value == UP)
      {
        player.stop();
        if (index == 1)
        {
          index = indexmax;
        }
        else
        {
          index--;
        }
        showMusicOnSD(index);
      }
      else if (results.value == DOWN)
      {
        player.stop();
        if (index == indexmax)
        {
          index = 1;
        }
        else
        {
          index++;
        }
        showMusicOnSD(index);
      }
      else if (results.value == LEFT)
      {

        player.stop();
        return -1;
        irrecv.resume();
      }
      else if (results.value == ONE)
      {
        Serial.println(player.readState());
        if (player.readState() == 1)
        {
          player.stop();
        }
        else
        {
          player.play(index);
        }
      }
      irrecv.resume();
    }
  }
}

void manageMainMenu()
{
  resetDisplay();

  updateMainMenu();

  while (currentMenu == MAINMENU)
  {
    bool menuSelected = waitForMenuSelection();
    if (menuSelected == true)
    {

      switch (mainMenuIndex)
      {
      case MAINMENUGETIPINFOSINDEX:
        currentMenu = GETIPINFOS;
        break;

      case MAINMENUDOWNLOADMUSICINDEX:
        // currentMenu = DOWNLOADMUSIC;
        break;
      case FETCHMUSICFILENAME:
        // currentMenu = FETCHMUSICFILENAME;
        break;
      case MAINMENUSETMUSICINDEX:
        currentMenu = CHOOSEMUSIC;
        break;
      }
    }
    else
    {
      break;
    }
  }
}
void manageGetIpInfos()
{
  showIpInformations(WiFi.localIP().toString().c_str(), WiFi.subnetMask().toString().c_str(), WiFi.gatewayIP().toString().c_str(), WiFi.SSID().c_str());
  while (results.value != LEFT)
  {
    if (irrecv.decode(&results))
    {
      irrecv.resume();
    }
  }
  currentMenu = MAINMENU;
}

void manageChooseMusicMenu()
{
  resetDisplay();
  int numberOfMusicFiles = folderCount;

  if (numberOfMusicFiles == -1)
  {
    currentMenu = MAINMENU;
    return;
  }
  int musicChoice = waitForMusicToSet(numberOfMusicFiles);

  if (musicChoice != -1)
  {
    choosenMusic = musicChoice;
    showMusicChoiceValidationScreen(choosenMusic);
    delay(3000);
  }

  currentMenu = MAINMENU;
  irrecv.resume();
  return;
}

void manageRestartConfirmAction()
{
  showRestartConfirmActionScreen();
  while (currentMenu == RESTARTCONFIRMACTION)
  {

    if (irrecv.decode(&results))
    {
      Serial.println(results.value);
      if (results.value == PAUSE)
      {
        ESP.restart();
      }
      else if (results.value == LEFT)
      {
        currentMenu = MAINMENU;
        irrecv.resume();
        return;
      }
      else
      {
        irrecv.resume();
      }
    }
  }
}

void manageAlarmClockMainScreen()
{
  showAlarmClockMainScreen(choosenMusic, musicVolume);
  while (currentMenu == ALARMCLOCKMAINSCREEN)
  {
    if (irrecv.decode(&results))
    {
      Serial.println(results.value);
      if (results.value == PAUSE)
      {
        currentMenu = MAINMENU;
        irrecv.resume();
        return;
      }
      else
      {
        irrecv.resume();
      }
    }
  }
}

void setup()
{

  Serial.begin(115200);
  // Serial2.begin(115200);

  // pinMode(Player_state, OUTPUT);

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

  /*
    if(!player.available()){
      currentMenu = FATALERROR;
    }
  */
  tft.fillScreen(ILI9341_BLACK);

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

  DFPSerial.begin(9600, SERIAL_8N1, /*rx =*/26, /*tx =*/27);

  Serial.println();
  Serial.println(F("DFPlayer Mini Demo"));

  if (!player.begin(DFPSerial, /*isACK = */ true, /*doReset = */ true))
  {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    showFatalErrorScreen();
    while (true)
      ;
  }

  player.stop();
  int count = player.readFileCounts();
  int fCount = player.readFolderCounts();
  folderCount = fCount;

  player.volume(musicVolume);
}

void loop()
{

  // put your main code here, to run repeatedly:

  if (currentMenu == FATALERROR)
  {
    showFatalErrorScreen();
    while (true)
    {
    }
  }

  switch (currentMenu)
  {
  case MAINMENU:
    manageMainMenu();
    break;
  case CHOOSEMUSIC:
    manageChooseMusicMenu();
    break;
  case RESTARTCONFIRMACTION:
    manageRestartConfirmAction();
    break;
  case ALARMCLOCKMAINSCREEN:
    manageAlarmClockMainScreen();
    break;
  case GETIPINFOS:
    manageGetIpInfos();
    break;
  }
}
