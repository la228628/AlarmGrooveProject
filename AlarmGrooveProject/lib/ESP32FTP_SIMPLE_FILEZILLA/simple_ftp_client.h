#ifndef __SIMPLE_FTP_CLIENT_H
#define __SIMPLE_FTP_CLIENT_H
#include <Arduino.h>
#include <WiFi.h>
#include <lwip/sockets.h>


bool connectToFTPServer();
bool disconnectFromFTPServer(); // Fonction ajoutée
uint8_t sendFTPCommand(const char *cmd);
bool loginFTPServer(String username , String password);
void readFTPResponse();
bool parseFTPDataPort();
bool downloadFileFromFTP(const char *path, int musicindex, const char *filename);
void getFile();
bool getLinesFromTxtFile(const char *path, String lineArray[]); // Fonction ajoutée
char *getFTPHost(); // Fonction ajoutée
void setFTPHost(char *ftpHost); // Fonction ajoutée
#endif
