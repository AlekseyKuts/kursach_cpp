#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <Windows.h>

#pragma warning(disable: 4996)

using namespace std;

int main(int argc, char* argv[]) {
	//WSAStartup
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Error: failed connect to server.\n";
		return 1;
	}
	char name[512];
	DWORD sizzze = 512;
	GetComputerNameA(name, &sizzze);
	send(Connection, name, sizeof(name), NULL);
	strcpy(name, inet_ntoa(addr.sin_addr));
	send(Connection, name, sizeof(name), NULL);
	cout << "Порт: " << addr.sin_port << "\n\n";
	system("pause");
	while (true) {
		char msg[512];
		recv(Connection, msg, sizeof(msg), NULL);
		if (strstr(msg, "system(\"CLS\"") != NULL) {
			system("CLS");
		}
		else if (strstr(msg, "system(\"pause\"") != NULL) {
			system("pause");
		}
		else if (strstr(msg, "cincincin") != NULL) {
			string snd;
			getline(cin, snd);
			char snd_c[512];
			strcpy(snd_c, snd.c_str());
			send(Connection, snd_c, sizeof(snd_c), NULL);
		}
		else if (strstr(msg, "endendend") != NULL) break;
		else std::cout << msg;
	}
	system("pause");
	return 0;
}