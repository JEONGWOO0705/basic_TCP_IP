#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 1024
void error_handling(char* message);
void send_image(int clnt_sock);

char webpage[] = "HTTP/1.1 200 OK\r\n"
                 "Server: Linux Web Server\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                 "<!DOCTYPE html>\r\n"
                 "<html><head><title>My Web Page</title>\r\n"
                 "<style>body { background-color: #FFFF00; text-align: center; }</style>\r\n"  
                 "</head>\r\n"
                 "<style>h1{color: pink;}</style></head>\r\n"
                 "<body><div><h1 style=\"color: pink;\">Hello World!!</h1><br>\r\n"  
                 "<img src=\"/game.jpg\"></div></body></html>\r\n";


const char* image_header = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: image/jpeg\r\n"
                           "Content-Length: ";

int main(int argc, char* argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout;
    fd_set reads, cpy_reads;

    socklen_t adr_sz;
    int fd_max, fd_num, i;
    char buf[BUF_SIZE];
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = serv_sock;

    while (1) {
        cpy_reads = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
            break;
        if (fd_num == 0)
            continue;

        for (i = 0; i <= fd_max; i++) {
            if (FD_ISSET(i, &cpy_reads)) {
                if (i == serv_sock) {
                    adr_sz = sizeof(clnt_adr);
                    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
                    FD_SET(clnt_sock, &reads);
                    if (fd_max < clnt_sock)
                        fd_max = clnt_sock;
                    printf("connected client: %d \n", clnt_sock);
                } else {
                    int str_len = read(i, buf, BUF_SIZE - 1);
                    if (str_len == 0) {
                        FD_CLR(i, &reads);
                        close(i);
                        printf("closed client: %d \n", i);
                    } else {
                        buf[str_len] = 0; // Null-terminate the request
                        send_image(i); // 이미지 전송
                        FD_CLR(i, &reads);
                        close(i);
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;
}

void send_image(int clnt_sock) {
    FILE *fp = fopen("game.jpg", "rb"); // 파일이 실행 파일과 같은 디렉토리에 있는지 확인
    if (fp == NULL) {
        error_handling("Failed to open image file");
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char header[BUF_SIZE];
    sprintf(header, "%s%ld\r\n\r\n", image_header, file_size);
    write(clnt_sock, header, strlen(header));

    char buf[BUF_SIZE];
    while (1) {
        int read_cnt = fread(buf, 1, BUF_SIZE, fp);
        if (read_cnt == 0)
            break;
        write(clnt_sock, buf, read_cnt);
    }

    fclose(fp);
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
