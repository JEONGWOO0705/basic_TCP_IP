#include<stdio.h>
#include<WinSock2.h>


int main(void) {
	SOCKET socket(int af, int type, int protocol); // 성공시 소켓 핸들, 실패시 INVALID_SOCKET 반환

	int bind(SOCKET s, const struct sockaddr* name, int namelen);
	// 성공시 0, 실패시 SOCKET_ERROR 반환

	int listen(SOCKET s, int backlog);
	// 성공시 0, 실패시 SOCKET_ERROR]

	SOCKET accept(SOCKET s, struct sockaddr* addr, int* addrlen);
	// 성공시 소켓핸들, 실패시 INVALID_SOCKET

	int connect(SOCKET s, const struct sockaddr* name, int namelen);
	// 성공시 0, 실패시 SOCKET_ERROR

	int closesocket(SOCKET s);
	// 성공시 0, 실패시 SOCKET_ERROR


}