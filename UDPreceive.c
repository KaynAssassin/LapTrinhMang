#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    bind(receiver, (SOCKADDR*)&addr, sizeof(addr));

    char buf[16];
    int ret;

    while (1)
    {
        ret = recvfrom(receiver, buf, sizeof(buf), 0, NULL, NULL);
        
        if (ret > 0)
        {
            buf[ret] = 0;
            printf("Received: %s\n", buf);
        }
        else
        {
            printf("recvfrom() failed\n");
        }
    }
}