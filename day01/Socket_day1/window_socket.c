#include<stdio.h>
#include<WinSock2.h>


int main(void) {
	SOCKET socket(int af, int type, int protocol); // ������ ���� �ڵ�, ���н� INVALID_SOCKET ��ȯ

	int bind(SOCKET s, const struct sockaddr* name, int namelen);
	// ������ 0, ���н� SOCKET_ERROR ��ȯ

	int listen(SOCKET s, int backlog);
	// ������ 0, ���н� SOCKET_ERROR]

	SOCKET accept(SOCKET s, struct sockaddr* addr, int* addrlen);
	// ������ �����ڵ�, ���н� INVALID_SOCKET

	int connect(SOCKET s, const struct sockaddr* name, int namelen);
	// ������ 0, ���н� SOCKET_ERROR

	int closesocket(SOCKET s);
	// ������ 0, ���н� SOCKET_ERROR


}