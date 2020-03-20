#include<stdio.h>
#include<winsock2.h>

#define _WINSOCK_DRPRECATED_NO_WARNINGS

int main(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	SOCKET client = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9000);
	
	int ret = connect(client,(SOCKADDR*)&addr,sizeof(addr));
	
	if(ret == SOCKET_ERROR){
		ret = WSAGetLastError();
		printf("Connect() failed:error code %d \n",ret);
		return 1;
	}
	
	char buf[256] = "Hello server";
	send(client,buf,strlen(buf),0);
	while(1){
		ret = recv(client,buf,sizeof(buf),0);
		if(ret <=0){
			printf("Connection lost\n");
			break;
		}
		if(ret < sizeof(buf)) buf[ret] = 0;
		printf("Received:%s\n",buf);
		
	}
	closesocket(client);
	WSACleanup();
}
