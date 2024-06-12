#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>	// 유닉스용
#include<sys/socket.h>

//#include <winsock2.h>	// 이거는 윈도우용
//#include <ws2tcpip.h>
//#pragma comment(lib, "ws2_32.lib")
void error_handling(char* message);

int main(int argc, char* argv[]) {
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[] = "Hello World!";

	if (argc != 2) {
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 소켓 생성
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));	// 32 ~ 37  소켓의 주소할당을 위해 구조체 변수를 초기화하고 bind함수를 호출
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	if (listen(serv_sock, 5) == -1) // 연결대기 상태, 연결요청 대기 큐의 크기도 5로 설정 --> 28행에서 생성한 소켓을 가리켜 서버 소켓이라 할 수 있다.
		error_handling("listen() error");
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); 
	// accept함수로 대기큐에서 첫번째로 대기중에 있는 연결 요청을 참조하여 클라이언트와의 연결을 구성, 
	//이때 생성된 소켓의 파일 디스크립터를 반환, 참고로 이함수가 호출되었을때 대기큐가 비어있는 상태라면, 대기큐가 찰때까지 , 
	//다시말해서 클라이언트의 연결요청이 들어올때까지 accept함수는 반환하지 않는다 
	if (clnt_sock == -1)
		error_handling("accept()error");

	write(clnt_sock, message, sizeof(message)); // 클라이언트에게 데이터를 전송
	close(clnt_sock); // 연결해제
	close(serv_sock);
	return 0;

}

void error_handling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
