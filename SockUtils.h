#pragma once;

#include <string>

class ClientConnectionInfo;

bool InitSocketsLib();
bool ReleaseSocketsLib();

void TestSockets();

void TestSendToServer();
void TestServerSocket();

void SendToClient(ClientConnectionInfo*, std::string msg);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<