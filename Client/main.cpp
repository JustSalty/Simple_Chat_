#include <WinSock2.h>
#include <thread>
#include <iostream>
#include "C:\Users\Admin\Documents\MyDocs\UNI\Course II\OOP\Chat\SockUtils.h"

using namespace std;

unsigned int DefaultPort_ = 10001;
const char *DefaultServerAddress_ = "127.0.0.1";
SOCKET s;
bool onServer = false;

void TestSendToServer0()
{
	string dataToSend;

	cin >> dataToSend;

	while (send(s, dataToSend.c_str(), dataToSend.length(), 0) != SOCKET_ERROR)
	{
		getline(cin, dataToSend);
		if (dataToSend == "quit") onServer = false;
	}

	closesocket(s);
}

void main()
{
	InitSocketsLib();

	s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(DefaultPort_);
	dest_addr.sin_addr.s_addr = inet_addr(DefaultServerAddress_);



	if (connect(s, (sockaddr *)&dest_addr, sizeof(dest_addr)) != 0)
	{
		cout << "Error connecting to server!";
		return;
	}

	thread send(TestSendToServer0);
	send.join();

	onServer = true;
	int bufSize = 100;
	char* buf = new char[bufSize];
	memset(buf, 0, bufSize);
	while (onServer && recv(s, buf, bufSize - 1, 0))
	{
		cout << buf << endl;
		memset(buf, 0, bufSize);
	}


	//TestSendToServer();
	//TestSockets();

	ReleaseSocketsLib();
}