#include<stdio.h>

int main(int argc, char* argv[]) {
	printf("전달하는 인자 갯수 : %d\n", argc);
	printf("실행 파일 : %s\n", argv[0]);

	for (int i = 1; i < argc; i++) {
		printf("전달 인자 : %s\n", argv[i]);
	}
}