#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    char buf[256];
    while (1)
    {
        printf("Enter a string: ");
        gets_s(buf);
        if (strcmp(buf, "exit") == 0)
            break;

        sendto(sender, buf, strlen(buf), 0, (SOCKADDR*)&addr, sizeof(addr));
    }

    closesocket(sender);
    WSACleanup();
}