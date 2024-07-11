#include <stdio.h>
#include "simple_ftp_client.h"
#include "SD_card_helper.h"

const char *ssid = "WiFi-2.4-2D90";
// const char* ssid     = "raspi-webgui";
const char *password = "wws7db5j9bu4k";

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
  /*
    listDir(."/", 0);
    createDir(."/mydir");
    listDir(."/", 0);
    removeDir(."/mydir");
    listDir(."/", 2);
    writeFile(."/hello.txt", "Hello ");
    appendFile(."/hello.txt", "World!\n");
    readFile(."/hello.txt");
    deleteFile(."/foo.txt");
    renameFile(."/hello.txt", "/foo.txt");
    readFile(."/foo.txt");
    testFileIO(."/test.txt");
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
  */

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
