#include "simple_ftp_client.h"
#include "SD_card_helper.h"

WiFiClient client;
WiFiClient dataclient;
WiFiClient ftpClient;

char *host = "192.168.1.9";
// char* host = "10.3.141.1";
unsigned int ftpPort = 21;
unsigned int DataPort = 1;

String recvBuf;
char ftpRespDataBuf[100] = {0};

bool connectToFTPServer()
{
  if (ftpClient.connected())
  {
    return true;
  }
  else if (!ftpClient.connect(host, ftpPort))
  {
    Serial.println("FTP Server connection failed");
    return false;
  }
  return true;
}

bool disconnectFromFTPServer()
{
  if (ftpClient.connected())
  {
    ftpClient.stop();
    return true;
  }
  ftpClient.stop();
  return true;
}

void readFTPResponse()
{
  recvBuf = "";
  String temp;
  char ch;
  for (int i = 0; i < 3; i++)
  {
    while (ftpClient.available())
    {
      ch = ftpClient.read(); // readStringUntil('\r');
      recvBuf += ch;
    }
  }
  Serial.print("> ");
  Serial.print(recvBuf);
  ftpClient.flush();
}

uint8_t sendFTPCommand(const char *cmd)
{
  int ret = 0;
  Serial.print("< ");
  Serial.println(cmd);
  ftpClient.println(cmd);
  delay(200);
  readFTPResponse();
  if (recvBuf.length())
    sscanf(recvBuf.c_str(), "%d ", &ret);
  return (uint8_t)ret;
}

bool loginFTPServer(String username, String password)
{
  if (!connectToFTPServer())
  {
    return false;
  }
  uint8_t ret = 0;
  char userCommand[50];
  sprintf(userCommand, "USER %s", username.c_str());
  ret = sendFTPCommand(userCommand);

  char passCommand[50];
  sprintf(passCommand, "PASS %s", password.c_str());
  ret = sendFTPCommand(passCommand);

  if (ret == 230)
  {
    return true;
  }
  else if (ret == 503)
  {
    disconnectFromFTPServer();
    return false;
  }
  return false;
}

bool parseFTPDataPort()
{
  char str[] = "";
  DataPort = 0;
  sscanf(recvBuf.c_str(), "229 Entering Extended Passive Mode (|||%d|)", &DataPort);
  Serial.printf("Port Parsed %d\n", DataPort);
  if (DataPort)
  {
    return true;
  }
  return false;
}

bool initFileDownloadSequence()
{
  return 0;
}

bool downloadFileFromFTP(const char *path, int musicindex, const char *filename)
{
  int socket_fd;
  struct sockaddr_in sa, ra;

  int recv_data = 0;
  uint8_t data_buffer[512];

  if (SD_rmFile(path) == false)
  {
    Serial.println("File Delete Failed");
  }
  else
  {
    Serial.println("File Deleted");
  }
  Serial.println("Downloading File");
  File file = SD.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return false;
  }

  socket_fd = socket(PF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0)
  {
    printf("socket call failed");
    return false;
  }

  /* Receiver connects to server ip-address. */

  memset(&ra, 0, sizeof(struct sockaddr_in));
  ra.sin_family = AF_INET;
  ra.sin_addr.s_addr = inet_addr(host);
  ra.sin_port = htons(DataPort);

  if (connect(socket_fd, (const sockaddr *)&ra, sizeof(struct sockaddr_in)) < 0)
  {
    printf("connect failed \n");
    close(socket_fd);
    return false;
  }

  int recvCount = 0;
  uint32_t t = millis();

  int ret = 0;

  char retrCommand[50];
  sprintf(retrCommand, "RETR /music/music%d.mp3", musicindex);
  //sprintf(retrCommand, "RETR %s", path);
  //sprintf(retrCommand, "RETR /music/%s", filename);

  Serial.println(retrCommand);
  if(path == "/names/names.txt")
  {
    ret = sendFTPCommand("RETR /names/names.txt");
  }
  else
  {
    ret = sendFTPCommand(retrCommand);
  }
  


  Serial.println("Downloading File after RETR command");
  while ((recv_data = recv(socket_fd, data_buffer, sizeof(data_buffer), 0)) > 0)
  {
    Serial.printf("Received %d bytes\n", recv_data);
    file.write(data_buffer, recv_data);
    recvCount += recv_data;
  }
  uint32_t ttotal = (millis() - t);
  Serial.println("File Download Completed CRC");
  // Serial.println(String("Time required Download File ") + (ttotal / 1000) + "sec File Size " + recvCount + " byte " + " Speed of file transfer " + ((recvCount / 1024) / (ttotal / 1000)) + " kbps");
  file.close();

  close(socket_fd);
  ftpClient.stop();
  return true;
}

void getFile()
{
  char ch;
  recvBuf = "";
  // memset(dataBuf, 0, sizeof(dataBuf));
  SD_rmFile("/names/names.txt");
  File file = SD.open("/names/names.txt", FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return;
  }
  unsigned int i = 0, j = 0;
  uint8_t dataBuf[512];
  client.connect(host, DataPort);
  // sendFTPCommand("RETR /home/pi/Downloads/test.txt");
  sendFTPCommand("RETR /names/names.txt");
  uint32_t t = millis();
  client.flush();
  while (client.connected())
  {
    while (client.available() > 0)
    {
      j = client.read(dataBuf, 4096);
      file.write(dataBuf, j);
      i += j;
    }
  }

  uint32_t ttotal = (millis() - t);
  delay(2);
  Serial.println("Name file getted");
  // Serial.println(String("Time required Download File ") + (ttotal / 1000) + "sec File Size " + i + "kb " + " Speed of file transfer " + ((i / 1024) / (ttotal / 1000)) + " kbps");
  client.stop();
  file.close();
}

bool getLinesFromTxtFile(const char *path, String lineArray[])
{
  File file = SD.open(path, FILE_READ);
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return false;
  }
  String fileContent = file.readString();
  Serial.print("File Content lines: ");
  Serial.println(fileContent.length());
  int nameCount = 0;
  int i = 0;
  while (i < fileContent.length())
  {
    int j = fileContent.indexOf("\n", i);
    if (j == -1)
    {
      j = fileContent.length();
    }
    lineArray[nameCount] = fileContent.substring(i, j);
    nameCount++;
    i = j + 1;
  }
  return true;
}

char *getFTPHost()
{
  return host;
}

void setFTPHost(char *ftpHost)
{
  host = ftpHost;
}
