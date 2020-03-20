#include<stdio.h>

#include<winsock2.h>

int main(){
	
	WSADATA wsa;
	
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	SOCKET listener = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	SOCKADDR)IN addr;
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htons(9000);
	
	bind(listener,(SOCKADDR*)&addr,sizeof(addr));
	
	listener(listener,5);
	
	SOCKET client = accept(listener,NULL,NULL);
	
	char buf[256];
	int ret = recv(client,buf,sizeof(buf),0);
	
	if(ret <= 0){
		return 1;
	}
	buf[ret] = 0;
	 printf("receive:%s \n",buf);
	 
	while(1){
		printf("Nhap du lieu tu ban phim:");
	 	get_s(buf);
	 	
	 	if(strcmp(buf,"exit") == 0) break;
	 	send(client,buf,sizeof(buf),0)
	 }
}
