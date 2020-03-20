#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addrinfo* info;

    int ret = getaddrinfo("bunoc.net", "http", NULL, &info);
    if (ret != 0)
    {
        printf("Khong phan giai duoc ten mien");
        return 1;
    }

    memcpy(&addr, info->ai_addr, info->ai_addrlen);

    ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        printf("Khong ket noi duoc");
        return 1;
    }

    const char* msg = "HEAD HTTP/1.1\r\nHost: bunoc.net\r\n\r\n";
    send(client, msg, strlen(msg), 0);

    char buf[2048];
    while (1)
    {
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
            break;

        if (ret < sizeof(buf))
            buf[ret] = 0;

        printf("%s", buf);
    }

    closesocket(client);
    WSACleanup();
}
