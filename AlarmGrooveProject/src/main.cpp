#include <stdio.h>
#include <Wifi.h>

#include <Preferences.h>

Preferences preferences;

const int emergencyPin = 14;



String ssid = "defaultSSID";
String password = "defaultPassword";
bool connectionFailed = false;

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#include "DFRobotDFPlayerMini.h"

#include "Wire.h"
#include "RTClib.h"

// Define the pins used for the display
#define TFT_CS 15
#define TFT_RST 4
#define TFT_DC 2

#include "RemoteTouch.h"

// Define the IR codes for the remote control
uint64_t POWER = 0xFFA25D;
uint64_t VOLUP = 0xFF629D;
uint64_t VOLDOWN = 0xFFA857;
uint64_t LEFT = 0xFF22DD;
uint64_t RIGHT = 0xFFC23D;
uint64_t PAUSE = 0xFF02FD;
uint64_t DOWN = 0xFFE01F;
uint64_t UP = 0xFF906F;
uint64_t ONE = 0xFF30CF;

void setUpButton(uint64_t ircode)
{
  UP = ircode;
  preferences.putULong("remoteUp", UP);
}

void setDownButton(uint64_t ircode)
{
  DOWN = ircode;
  preferences.putULong("remoteDown", DOWN);
}

void setLeftButton(uint64_t ircode)
{
  LEFT = ircode;
  preferences.putULong("remoteLeft", LEFT);
}

void setRightButton(uint64_t ircode)
{
  RIGHT = ircode;
  preferences.putULong("remoteRight", RIGHT);
}

void setSelectButton(uint64_t ircode)
{
  PAUSE = ircode;
  preferences.putULong("remotePause", PAUSE);
}

void setPowerButton(uint64_t ircode)
{
  POWER = ircode;
  preferences.putULong("remotePower", POWER);
}

void setVolumeUpButton(uint64_t ircode)
{
  VOLUP = ircode;
  preferences.putULong("remoteVolUp", VOLUP);
}

void setVolumeDownButton(uint64_t ircode)
{
  VOLDOWN = ircode;
  preferences.putULong("remoteVolDown", VOLDOWN);
}

void setOneButton(uint64_t ircode)
{
  ONE = ircode;
  preferences.putULong("remoteOne", ONE);
}

#include "MenuIndexReferences.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

#include "DisplayFunctions.h"
#include "pictocode.h"

// Define the pin for the mp3 player state
int Player_state = 13;

static const uint8_t PIN_MP3_TX = 27; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 26; // Connects to module's TX
#define DFPSerial Serial1
DFRobotDFPlayerMini player;

const uint16_t kRecvPin = 16;

IRrecv irrecv(kRecvPin);

decode_results results;

int mainMenuIndex = 1;

int currentMenu = ALARMCLOCKMAINSCREEN;

int choosenMusic = 1;
int musicVolume = 2;
int folderCount = 0;

#include <HTTPClient.h>
#include <ArduinoJson.h>

float temperature = 0;
int pictocode = 0;

String lat = "50.600004741970174";
String lon = "3.625515300047851";
String api_key = "wKNTjiRedyF1ZOc0";
String api_endpoint;

RTC_DS3231 rtc;

int hour = 0;
int minute = 0;
int alarmHour = 0;
int alarmMinute = 0;
bool alreadyTriggered = false;

void getWeatherInformations()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    api_endpoint = "https://my.meteoblue.com/packages/current?lat=" + lat + "&lon=" + lon + "&apikey=" + api_key;

    Serial.println(api_endpoint);

    http.begin(api_endpoint);
    int httpCode = http.GET();

    if (httpCode > 0)
    {
      String payload = http.getString();
      Serial.println(payload);

      DynamicJsonDocument doc(2048);
      DeserializationError error = deserializeJson(doc, payload);

      if (!error)
      {
        int pcode = doc["data_current"]["pictocode"];
        float to = doc["data_current"]["temperature"];

        pictocode = pcode;
        temperature = to;
      }
      else
      {
        Serial.println("Error parsing JSON");
      }
    }
    else
    {
      Serial.println("Error in HTTP request");
    }

    http.end();
  }
}

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
        modifyShowMusicOnSD(index);
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
        modifyShowMusicOnSD(index);
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

      case MAINMENUSETVOLUME:
        currentMenu = SETVOUME;
        break;
      case MAINSERIALCOMMENUINDEX:
        currentMenu = SERIALCOM;
        break;
      case MAINMENUSETMUSICINDEX:
        currentMenu = CHOOSEMUSIC;
        break;
      case MAINMENUSETALARMTIMEINDEX:
        currentMenu = SETALARMTIME;
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
  showIpInformations(WiFi.localIP().toString().c_str(), WiFi.subnetMask().toString().c_str(), WiFi.gatewayIP().toString().c_str(), ssid.c_str());
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

  if (numberOfMusicFiles == 0)
  {
    showNoMusicOnSD();
    delay(3000);
    currentMenu = MAINMENU;
    return;
  }
  int musicChoice = waitForMusicToSet(numberOfMusicFiles);

  if (musicChoice != -1)
  {
    choosenMusic = musicChoice;
    preferences.putUInt("choosenMusic", choosenMusic);
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

void manageSetAlarmTime()
{
  int h = hour;
  int m = minute;
  showSetAlarmTimeScreen(h, m);
  while (currentMenu == SETALARMTIME)
  {
    if (irrecv.decode(&results))
    {
      Serial.println(results.value);
      if (results.value == PAUSE)
      {
        alarmHour = h;
        preferences.putUInt("alarmHour", alarmHour);
        alarmMinute = m;
        preferences.putUInt("alarmMinute", alarmMinute);
        currentMenu = MAINMENU;
        irrecv.resume();
        return;
      }
      else if (results.value == UP)
      {
        if (h < 23)
        {
          h++;
        }
        else
        {
          h = 0;
        }
        modifySetAlarmTimeScreen(h, m);
        irrecv.resume();
      }
      else if (results.value == DOWN)
      {
        if (h > 0)
        {
          h--;
        }
        else
        {
          h = 23;
        }
        modifySetAlarmTimeScreen(h, m);
        irrecv.resume();
      }
      else if (results.value == LEFT)
      {
        currentMenu = MAINMENU;
        irrecv.resume();
        return;
      }
      else if (results.value == VOLUP)
      {
        if (m < 59)
        {
          m++;
        }
        else
        {
          m = 0;
        }
        modifySetAlarmTimeScreen(h, m);
        irrecv.resume();
      }
      else if (results.value == VOLDOWN)
      {
        if (m > 0)
        {
          m--;
        }
        else
        {
          m = 59;
        }
        modifySetAlarmTimeScreen(h, m);
        irrecv.resume();
      }
      else
      {
        irrecv.resume();
      }
    }
  }
}
void getCurrentTime()
{
  DateTime now = rtc.now();
  int h = now.hour();
  int m = now.minute();
  hour = h;
  minute = m;
  Serial.print(h);
  Serial.print(":");
  Serial.println(m);
}
void manageAlarmClockMainScreen()
{

  irrecv.resume();

  getCurrentTime();

  showAlarmClockMainScreen(choosenMusic, musicVolume, temperature, getPictocodeDescription(pictocode), lat, lon, hour, minute, alarmHour, alarmMinute);
  while (currentMenu == ALARMCLOCKMAINSCREEN)
  {
    int previousHour = hour;
    int previousMinute = minute;
    DateTime now = rtc.now();

    if (now.hour() != previousHour)
    {
      getWeatherInformations();
    }

    if (now.minute() != previousMinute || now.hour() != previousHour)
    {
      getCurrentTime();
      modifyAlarmClockScreen(hour, minute, temperature, getPictocodeDescription(pictocode));
      alreadyTriggered = false;

      if (hour == alarmHour && minute == alarmMinute && alreadyTriggered == false && choosenMusic != 0)
      {

        player.loop(choosenMusic);
        while (true)
        {
          previousHour = hour;
          previousMinute = minute;
          DateTime now = rtc.now();
          if (now.hour() != previousHour || now.minute() != previousMinute)
          {
            getCurrentTime();
            modifyAlarmClockScreen(hour, minute, temperature, getPictocodeDescription(pictocode));
          }
          if (irrecv.decode(&results))
          {
            if (results.value == PAUSE)
            {
              player.stop();
              alreadyTriggered = true;
              irrecv.resume();
              break;
            }
            else
            {
              irrecv.resume();
            }
          }
        }
      }
    }

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
void manageSetVolume()
{
  showSetVolumeScreen(musicVolume);
  int volume = musicVolume;
  while (currentMenu == SETVOUME)
  {
    if (irrecv.decode(&results))
    {
      Serial.println(results.value);
      if (results.value == PAUSE)
      {
        musicVolume = volume;
        preferences.putUInt("musicVolume", musicVolume);
        player.volume(musicVolume);
        currentMenu = MAINMENU;
        irrecv.resume();
        return;
      }
      else if (results.value == VOLUP)
      {
        if (volume < 30)
        {
          volume++;
          modifySetVolumeScreen(volume);
          irrecv.resume();
        }
        else
        {
          volume = 30;
          irrecv.resume();
        }
      }
      else if (results.value == VOLDOWN)
      {
        if (volume > 1)
        {
          volume--;
          modifySetVolumeScreen(volume);
          irrecv.resume();
        }
        else
        {
          volume = 1;
          irrecv.resume();
        }
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

void manageSerialCom()
{

  String _ssid = ssid;
  String _password = password;
  String _lat = lat;
  String _lon = lon;
  String _api_key = api_key;

  bool dataSend = false;

  showWaitForDataScreen();

  while (currentMenu == SERIALCOM)
  {
    if (dataSend == false)
    {

      if (Serial.available() > 0)
      {
        String receivedData = Serial.readStringUntil('\n'); 

        if (receivedData.startsWith("SSID:") && receivedData.equals("SSID:default") == false)
        {
          _ssid = receivedData.substring(5); 
          
        }
        else if (receivedData.startsWith("PASSWORD:") && receivedData.equals("PASSWORD:default") == false)
        {
          _password = receivedData.substring(9);
        }
        else if (receivedData.startsWith("LATITUDE:") && receivedData.equals("LATITUDE:default") == false)
        {
          _lat = receivedData.substring(9); 
        }
        else if (receivedData.startsWith("LONGITUDE:") && receivedData.equals("LONGITUDE:default") == false)
        {
          _lon = receivedData.substring(10); 
        }
        else if (receivedData.startsWith("APIKEY:"))
        {
          if (receivedData.equals("APIKEY:default") == false)
          {
            _api_key = receivedData.substring(7);
          }
          dataSend = true;
        }
      }
    }
    else
    {
      showConfirmInfosScreen(_ssid.c_str(), _password.c_str(), _lat.c_str(), _lon.c_str(), _api_key.c_str());
      while (dataSend == true)
      {
        if (irrecv.decode(&results))
        {
          if (results.value == LEFT)
          {
            irrecv.resume();
            return;
          }
          else if (results.value == RIGHT)
          {
            currentMenu = MAINMENU;
            preferences.putString("ssid", _ssid);

            preferences.putString("password", _password);

            preferences.putString("lat", _lat);

            preferences.putString("lon", _lon);

            preferences.putString("api_key", _api_key);
            irrecv.resume();
            ESP.restart();
          }
          else
          {
            irrecv.resume();
          }
        }
      }
    }
  }
}

void manageEmergency()
{
  struct ButtonAction
  {
    const char *prompt;
    void (*setButtonFunc)(uint64_t);
  } buttonActions[] = {
      {"Press PAUSE Button", setSelectButton},
      {"Press UP Button", setUpButton},
      {"Press DOWN Button", setDownButton},
      {"Press LEFT Button", setLeftButton},
      {"Press RIGHT Button", setRightButton},
      {"Press POWER Button", setPowerButton},
      {"Press VOLUP Button", setVolumeUpButton},
      {"Press VOLDOWN Button", setVolumeDownButton},
      {"Press ONE Button", setOneButton}};

  for (auto &action : buttonActions)
  {
    bool buttonDetected = false;
    showRemoteWaitingScreen(action.prompt);
    irrecv.resume();
    while (!buttonDetected)
    {
      if (irrecv.decode(&results))
      {
        action.setButtonFunc(results.value);
        delay(500);
        irrecv.resume();
        buttonDetected = true;
      }
    }
  }
  
}

void setup()
{

  Serial.begin(115200);

  preferences.begin("alarmclock", false);

  if (preferences.isKey("ssid"))
  {
    String ssidString = preferences.getString("ssid", "");
    if (ssidString != "")
    {
      ssid = ssidString;
    }
  }

  if (preferences.isKey("password"))
  {
    String passwordString = preferences.getString("password", "");
    if (passwordString != "")
    {
      password = passwordString;
    }
  }

  if (preferences.isKey("musicVolume"))
  {
    musicVolume = preferences.getUInt("musicVolume");
  }
  if (preferences.isKey("choosenMusic"))
  {
    choosenMusic = preferences.getUInt("choosenMusic");
  }
  if (preferences.isKey("alarmHour"))
  {
    alarmHour = preferences.getUInt("alarmHour");
  }
  if (preferences.isKey("alarmMinute"))
  {
    alarmMinute = preferences.getUInt("alarmMinute");
  }
  if (preferences.isKey("lat"))
  {
    lat = preferences.getString("lat");
  }
  if (preferences.isKey("lon"))
  {
    lon = preferences.getString("lon");
  }
  if (preferences.isKey("api_key"))
  {
    api_key = preferences.getString("api_key");
  }
  if (preferences.isKey("remoteUp"))
  {
    setUpButton(preferences.getULong("remoteUp"));
  }
  if (preferences.isKey("remoteDown"))
  {
    setDownButton(preferences.getULong("remoteDown"));
  }
  if (preferences.isKey("remoteLeft"))
  {
    setLeftButton(preferences.getULong("remoteLeft"));
  }
  if (preferences.isKey("remoteRight"))
  {
    setRightButton(preferences.getULong("remoteRight"));
  }
  if (preferences.isKey("remotePause"))
  {
    setSelectButton(preferences.getULong("remotePause"));
  }
  if (preferences.isKey("remotePower"))
  {
    setPowerButton(preferences.getULong("remotePower"));
  }
  if (preferences.isKey("remoteVolUp"))
  {
    setVolumeUpButton(preferences.getULong("remoteVolUp"));
  }
  if (preferences.isKey("remoteVolDown"))
  {
    setVolumeDownButton(preferences.getULong("remoteVolDown"));
  }
  if (preferences.isKey("remoteOne"))
  {
    setOneButton(preferences.getULong("remoteOne"));
  }

  


  Wire.begin();
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, let's set the time!");
    // Comment or adjust this line depending on how you want to set the time
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  irrecv.enableIRIn(); // Start the receiver
  while (!Serial)      // Wait for the serial connection to be establised.
    delay(100);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);

  tft.begin();
  tft.setFont();
  tft.setRotation(3);

  pinMode(emergencyPin, INPUT_PULLUP);
  int time = 0;
  bool emergency = false;
  showEmergencyWaitScreen();

  // Check if the emergency button is pressed in the first 5 seconds
  while (time < 5000)
  {
    if (digitalRead(emergencyPin) == LOW)
    {
      emergency = true;
      break;
    }
    time += 100;
    delay(100);
  }

  if (emergency)
  {
    manageEmergency();
  }
  irrecv.resume();

  showWelcomeScreen();
  delay(1000);
  tft.fillScreen(ILI9341_BLACK);
  Serial.println("SSID:");
  Serial.println(ssid);
  Serial.println("PASSWORD:");
  Serial.println(password);

  WiFi.begin(ssid, password);

  showWifiConnectionWaitScreen();
  while (WiFi.status() != WL_CONNECTED && connectionFailed == false)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.print(WiFi.status());

    if(irrecv.decode(&results))
    {
      if(results.value == PAUSE)
      {
        connectionFailed = true;
      }
      irrecv.resume();
    }
    
    if (WiFi.status() == WL_NO_SSID_AVAIL || WiFi.status() == WL_CONNECT_FAILED )
    {
      Serial.println("Connection failed");
      Serial.println(WiFi.status());  
      connectionFailed = true;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (connectionFailed == false)
  {

    showWifiConnectionSuccessScreen(WiFi.localIP().toString().c_str());
    getWeatherInformations();
  }
  else
  {
    showWifiConnectionFailedScreen();
  }
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

  Serial.print("File counts: ");
  Serial.println(folderCount);

  if(choosenMusic > folderCount)
  {
    choosenMusic = 1;
  }

  if(folderCount==0)
  {
    choosenMusic = 0;
  }

  player.volume(musicVolume);
}

void loop()
{

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

  case SETVOUME:
    manageSetVolume();
    break;

  case SETALARMTIME:
    manageSetAlarmTime();
    break;

  case SERIALCOM:
    manageSerialCom();
    break;
  }
}
