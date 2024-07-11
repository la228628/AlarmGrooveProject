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

  default:
    tft.println(mainMenuIndex);
    break;
  }
}

void updateMenu()
{
  unSelectAll();
  selectMenuIndex();
}

String waitForPause()
{
  while (true)
  {
    if (irrecv.decode(&results))
    {
      if (results.value == PAUSE)
      {
        irrecv.resume();
        return "PAUSE";
      }
      else if (results.value == UP)
      {
        if (mainMenuIndex > 1)
        {
          mainMenuIndex--;
        }
        else
        {
          mainMenuIndex = 4;
        }
        updateMenu();
        irrecv.resume();
      }
      else if (results.value == DOWN)
      {
        if (mainMenuIndex < 4)
        {
          mainMenuIndex++;
        }
        else
        {
          mainMenuIndex = 1;
        }
        updateMenu();
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



void showIpInformations()
{
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
  updateMenu();
}






















void setup()
{

  Serial.begin(115200);
  Serial2.begin(115200);

  if (!SD_Initialize())
  {
    Serial.println("Card Mount Failed");
    return;
  }
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    delay(500);
    Serial.print(".");
    delay(500);
    Serial.print(".");
    delay(500);
    Serial.println("");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE)
  {
    Serial.println("No SD card attached");
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC)
  {
    Serial.println("MMC");
  }
  else if (cardType == CARD_SD)
  {
    Serial.println("SDSC");
  }
  else if (cardType == CARD_SDHC)
  {
    Serial.println("SDHC");
  }
  else
  {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);


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


  if (downloadFileFromFTP("/names/names.txt", 0, "") == false)
  {
    Serial.println("File Download Failed");
  }
  else
  {
    Serial.println("File Downloaded");
  }

  delay(5000);









  String nameList[255];
  if (getLinesFromTxtFile("/names/names.txt", nameList))
  {
    for (int i = 0; i < 255; i++)
    {
      if (nameList[i] != "")
        Serial.println(nameList[i]);
    }
  }
  else
  {
    Serial.println("Failed to get names from file");
  }

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

  /*
    Serial.println("Getting File List...");
    listDir("/music", 0);
    Serial.println("File List Received");

    delay(3000);
  */
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
}

void loop()
{
}
