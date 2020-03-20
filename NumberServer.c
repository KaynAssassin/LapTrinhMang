#include <stdio.h>

#include <winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);

    SOCKET client = accept(listener, NULL, NULL);

    char buf[256];
    int ret;
    float f;

    while (1)
    {
        ret = recv(client, (char *)&f, sizeof(f), 0);
        if (ret <= 0)
        {
            printf("recv() failed\n");
            return 1;
        }

        // memcpy(&f, buf, sizeof(f));
        printf("Received: %f\n", f);
    }

    closesocket(client);
    closesocket(listener);
    WSACleanup();
}