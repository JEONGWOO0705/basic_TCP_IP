#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, char* argv[]) {
	//htons에서 h는 호스트 바이트 순서 , n은 네트워크 바이트 순서를 의미한다
	// s는 short, l은 long 
	// --->>> h, to, n , s의 조합으로 해석

	
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr = 0x12345678;
	unsigned long net_addr;

	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	printf("Host ordered port : %#x \n", host_port);
	printf("Network ordered port: %#x \n", net_port);
	printf("Host ordered address: %#;x \n", host_addr);
	printf("Network ordered address : %#lx \n", net_addr);
	return 0;
}