# basic-IoTNetwork-2024
IoT 개발자과정 IoT네트워크 프로그래밍 리포지토리

## 1일차(2024-06-11)
- 네트워크의 구성
    - cmd > ipconfig
    - IPv4
    - IPv6 - IPv4가 고갈되었을때를 대비하여 만들어둔 것
    - 기본 게이트웨이 - 컴퓨터로 들어오는 출입문
    
    - 전송하는 방식
        - TCP 
        - UDP

- 소말리아
    - 소 -> 소켓(socket)
    - 말 -> 바인더(bind)
    - 리 -> 리슨(listen)
    - 아 -> 엑셉트(accept)

- 네트워크 프로그래밍이란?
    - 소켓이란 것을 기반으로 프로그래밍을 하기 때문에 소켓 프로그래밍이라고도 함.
    - 네트워크로 연결된 둘 이상의 컴퓨터 사이에서의 데이터 송수신 프로그램의 작성을 의미함.

- 소켓
    - 소켓에 대한 간단한 이해
        - 네트워크(인터넷)의 연결 도구
        - 운영체제에 의해 제공이 되는 소프트웨어적인 장치
        - 소켓은 프로그래머에게 데이터 송수신에 대한 물리적, 소프트웨어적 세세한 내용을 신경 쓰지 않게 한다.

    - 소켓의 생성과정
        - 1단계 - 소켓생성
        - 2단계 - IP주소와 PORT번호 할당
        - 3단계 - 연결요청 가능상태로 변경
        - 4단계 - 연결요청에 대한 수락

- 윈도우 기반으로 구현(pass)

- 프로토콜 체계
    - PF_INET만 알면됨
    - PF_INET - IPv4 인터넷 프로토콜 체계

- 소켓의 타입
    - 연결지향형 소켓(TCP)
        - 중간에 데이터가 소멸되지 않고 목적지로 전송된다.
        - 전송 순서대로 데이터가 수신된다.
        - 전송되는 데이터의 경계가 존재하지 않는다.
    - 비연결지향형 소켓(UDP)
        - 전송된 데이터는 손실의 우려가 있고, 파손의 우려가 있다.
        - 전송되는 데이터의 경계가 존재.
        - 한번에 전송할 수 있는 데이터의 크기가 제한된다.

- 인터넷 주소
    - IPv4 - 4바이트 주소체계
    - IPv6 - 16바이트 주소체계

- 클래스 별 네트워크 주소와 호스트 주소의 경계
    - 클래스 A의 첫번째 바이트 범위 0~127
    - 클래스 B의 첫번째 바이트 범위 128~191
    - 클래스 C의 첫번째 바이트 범위 192~223

- 구조체 sockaddr_in의 멤버
    - 멤버 sin_family
        - 주소체계 정보저장
        - AF_INET - IPv4 인터넷 프로토콜에 적용하는 주소체계
        - AF_INET6 - IPv6 인터넷 프로토콜에 적용하는 주소체계
        - AF_LOCAL - 로컬 통신을 위한 유닉스 프로토컬의 주소체계
    - 멤버 sin_port
        - 16비트 PORT번호 저장
        - 네트워크 바이트 순서로 저장
    - 멤버 sin_addr
        - 32비트 IP주소 정보저장
        - 네트워크 바이트 순서로 저장
        - 멤버 sin_addr의 구조체 자료형 in_addr 사실상 32비트 정수자료형
    - 멤버 sin_zero
        - 특별한 의미를 지니지 않는 멤버
        - 반드시 0으로 채워야 한다.

``` C
    serv_addr.sin_famliy=AF_INET; // IPv4 인터넷 프로토콜을 적용하겠다는 의미
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
```

``` C
    printf("전달하는 인자개수 : %d\n", argc);
            printf("실행파일 : %s\n", argv[0]);
            
            for(int i = 1; i < argc; i++) {
                    printf("전달인자: %s\n", argv[i]);
            }
```
- 실행결과
        <img src="https://raw.githubusercontent.com/been2525/basic-IoTNetwork-2024/main/image/example001.png" width="730">

- CPU가 데이터를 메모리에 저장하는 방식
    - 빅 엔디안 - 상위 바이트의 값을 작은 번지수에 저장하는 방식 - 하위 바이트값을 큰 번지수에 저장
    - 리틀 엔디안 - 상위 바이트의 값을 큰 번지수에 저장하는 방식 - 하위 바이트값을 작은 번지수에 저장

- 바이트 순서의 변환
    - unsigned short htons(unsigned short);
    - unsigned short ntohs(unsigned short);
    - unsigned long htonl(unsigned long);
    - unsigned long ntohl(unsigned long);
        - htons에서 h는 호스트 바이트 순서를 의미
        - htons에서 n은 네트워크 바이트 순서를 의미
        - htons에서 s는 자료형 short를 의미
        - htonl에서 l은 자료형 long을 의미

## 2일차 (2024-06-12)
- TCP/IP 프로토콜 스택
    - 인터넷 기반의 데이터 송수신을 목적으로 설계된 스택
    - 큰 문제를 작게 나눠서 계층화 한 결과
    - 데이터 송수신의 과정을 네개의 영역으로 계층화 한 결과
    - 각 스택 별 영역을 전문화하고 표준화함
    - 7계층으로 세분화가 되며, 4계층으로도 표현함

- LINK 계층의 기능 및 역할
    - 물리적인 영역의 표준화 결과
    - LAN, WAN, MAN과 같은 물리적인 네트워크 표준 관련 프로토콜이 정의된 영역

- IP 계층의 기능 및 역할
    - IP는 Internet protocol을 의미
    - 경로의 설정과 관련이 있는 프로토콜

- TCP/UDP 계층의 기능 및 역할
    - 실제 데이터의 송수신과 관련 있는 계층
    - 전송계층으라고도 함.
    - TCP는 데이터의 전송을 보장하는 프로토콜, UDP는 보장하지 않는 프로토콜

- APPLICATION 계층
    -

- 연결요청 대기상태로의 진입
```c
#include <sys/type.h>

int listen(int sock, int backlog);
```

- 클라이언트의 연결요청 수락
```c
#include <sys/socket.h>

int accept(int sock,struct sockaddr * addr, socklen_t * addrlen);
```

- Tcp 클라이언트의 기본적인 함수호출 순서
    1. socket() - 소켓생성
    2. connect() - 연결요청
    3. read()/write()  - 데이터 송수신
    4. close() - 연결종료
```c
#include <sys/socket.h>

int connect(int sock, const struct sockaddr * servaddr, socklen_t addrlen);
```

- TCP 소켓에 존재하는 입출력 버퍼
    - 입출력 버퍼는 TCP 소켓 각각에 대해 별도로 존재한다.
    - 입출력 버퍼는 소켓생성시 자동으로 생성된다.
    - 소켓을 닫아도 출력버퍼에 남아있는 데이터는 계속해서 전송이 이뤄진다.
    - 소켓을 닫으면 입력버퍼에 남아있는 데이터는 소멸되어버린다.

- UDP 소켓의 특성과 동작원리
    - UDP 소켓은 SEQ,ACK와 같은 메시지 전달을 하지않는다.
    - 그리고 연결의 설정과 해제의 과정도 존재하지 않는다.
    - 때문에 데이터의 분실 및 손실의 위험이 있다.
    - 그러나 확인의 과정이 존재하지 않기 때문에 데이터의 전송이 빠르다.
    - 따라서 안전성보다 성능이 중요시 될 때에는 UDP를 사용한다.

- UDP의 데이터 송수신
    - TCP는 1대1의 연결을 필요로 하지만, UDP는 연결의 개념이 존재하지 않는다.
    - 서버 소켓과 클리이언트 소켓의 구분이 없다.

## 3일차
- connected UDP 소켓
    - unconnected UDP 소켓의 sendto함수 호출과정
        1. UDP 소켓에 목적지의 IP와 PORT번호 등록
        2. 데이터 전송
        3. UDP소켓에 등록된 목적지 정보 삭제
    - connected UDP 소켓의 경우 1단계와 3단계의 과정을 매회 거치지 않는다.
    - connceted UDP 소켓은 TCP와 같이 상대 소켓과의 연결을 의미하지 않는다.
    - 그러나 소켓에 목적지에 대한 정보는 등록이 된다.

- TCP 기반의 Half-close
    - close 및 closesocket 함수의 기능
        - 소켓의 완전 소멸을 의미한다.
        - 소켓이 소멸되므로 더 이상의 입출력은 불가능하다.
        - 상대방의 상태에 상관없이 일방적은 종료의 형태를 띤다.
        - 때문에 상대 호스트의 데이터 송수신이 아직 완료되지 않은 상황이라면, 문제가 발생할 수 있다.
    - Half-close
        - 종료를 원한다는 것은, 더 이상 전송할 데이터가 존재x
        - 따라서 출력 스트림은 종료를 시켜도된다.
        - 다만 상대방도 종료를 원하는지 확인되지 않은 상황이므로, 출력스트림은 종료시키지 않을 필요가 있다.
        - 때문에 일반적으로 Half-close라 하면 입력스트림만 종료하는 것을 의미한다.
    - Shut-down 함수
        - SHUT_RD - 입력 스트림 종료
        - SHUT_WR - 출력 스트림 종료
        - SHUT_RDWR - 입출력 스트림 종료

- Domain name system
    - 도메인 이름
        - IP를 대신하는 서버의 주소
        - 실제 접속에 사용되는 주소는 아니다. 이 정보는 IP로 변환이 되어야 접속이 가능하다.
    - DNS 서버
        - 도메인 이름을 IP로 변환해주는 서버
        - DNS는 일종의 분산 데이터베이스 시스템이다.
    - h_name - 공식 도메인 이름
    - h_aliases - 별칭의 도메인 이름
    - h_addrtype - 반환된 IP의 정보가 IPv4인 경우, AF_INET이 반환
    - h_length - 반환된 IP정보의 크기, IPv4의 경우 4, IPv6의 경우 16이 저장
    - h_addr_list - IP의 주소정보, 둘 이상의 경우 모두 반환

- IP주소를 이용해서 도메인 정보 얻어오기
```c
#include <netdb.h>

struct hostent * gethostbyaddr(const char * addr, socklen_t len, int family);
```

- 옵션정보의 참조에 사용되는 함수
```c
#include <sys/socket.h>

int getsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen);
```
- 옵션정보의 설정에 사용되는 함수
```c
#include <sys/socket.h>

int setsockopt(int sock,. int level, int optname, const void *optval, socklen_t optlen);
```
- 입력버퍼의 크기를 참조 및 변경할 때에는 SO_SNDBUF
- 출력버퍼의 크기를 참조 및 변경할 때에는 SO_RCVBUF

- time-wait
    - time-wait의 이해
        - 서버, 클라이언트에 상관없이 TCP 소켓에서 연결의 종료를 목적으로 Four-way handshaking의 첫 번째 메시지를 젂달하는 호스트의 소켓은 Time-wait 상태를 거친다.
    - time-wait은 길어질 수 있다.
        - Time-wait은 필요하다. 그러나 실 서비스중인 서버의 경이 Time-wait이 문제가 될 수 있다. 그러한 경우에는 Time-wait 상태에 있는 Port의 할당이 가능하도록 코드를 수정해야 한다.
- Nagle 알고리즘
    - Nagle 알고리즘은 앞서 전송한 데이터에 대한 ACK 메시지를 받아야만, 다음 데이터를 전송하는 알고리즘이다!

- 프로세스
    - 간단하게는 실행 중인 프로그램을 뜻한다.
    - 실행중인 프로그램에 관련된 메모리, 리소스 등을 총칭하는 의미이다.
    - 멀티프로세스 운영체제는 둘 이상의 프로세스를 동시에 생성 가능하다.

- 좀비 프로세스란?
    - 실행이 완료되었음에도 불구하고, 소멸되지 않은 프로세스
    - 프로세스도 main 함수가 반환되면 소멸되어야 한다.
    - 소멸되지 않았다는 것은 프로세스가 사용한 리소스가 메모리 공간에 여전히 존재한다는 의미이다.

- 좀비 프로세스의 생성원인
    - 자식프로세스가 종료되면서 반환하는 상태 값이 부모 프로세스에게 전달되지 않으면 해당 프로세스는 소멸되지 않고 좀비가 된다.


## 4일차(2024-06-14)
- 좀비프로세스의 소멸
    1. wait 함수의 사용
    2. waitpid 함수의 사용

- 시그널 핸들링    
    - 시그널이란
        - 특정 상황이 되었을때 운영체제가 프로세스에게 해당 상황이 발생했음을 알리는 일종의 메시지를 가리켜 시그널이라 한다.
        - 등록 가능한 시그널의 예
            - SIGALRM - alarm 함수 호출을 통해서 등록된 시간의 된 상황
            - SIGINT - CTRL+C가 입력된 상황
            - SIGCHLD - 자식 프로세스가 종료된 상황
    - 시그널 등록이란?
        - 특정 상황에서 운영체제로부터 프로세스가 시그널을 받기 위해서는 해당 상황에 대해서 등록의 과정을 거쳐야 한다.
    - 시그널 함수
        - signal(SIGCHLD, mychild); - 자식 프로세스가 종료되면 mychild 함수를 호출해 달라!
        - signal(SIGALRM, timeout); - alarm 함수호출을 통해서 등록된 시간이 지나면 timeout 함수호출!
        - signal(SIGINT, keycontrol); - CTRL+C가 입력되면 keycontrol 함수를 호출해 달라!
    - sigaction 함수
    ```C
    #include <signal.h>
    int sigaction(int signo, const sturct sigaction * act,struct sigaction * oldact);
    ```
- 멀티태스킹 기반의 다중접속 서버
    1. 에코서버(부모 프로세스)는 accept 함수호출을 통해서 연결요청을 수락한다.
    2. 이때 얻게 되는 소켓의 파일 디스크립터를 자식 프로세스를 생성해서 넘겨준다.
    3. 자식프로세스는 전달받은 파일 디스크립터를 바탕으로 서비스를 제공한다.

- 프로세스간 통신
    - 두 프로세스 사이에서의 데이터 전달
    - 두 프로세스 사이에서 데이터전달이 가능하려면, 두 프로세스가 함께 공유하는 메모리가 존재해야 한다.
- 프로세스간 통신의 어려움
    - 모든 프로세스는 자신만의 메모리 공간을 독립적으로 구성한다.
    - 즉, A프로세스는 B프로세스의 메모리 공간에 접근이 불가능하고, B 프로세스는 A 프로세스의 메모리 공간접근이 불가능하다.
    - 따라서 운영체제가 별도의 메모리 공간을 마려해 줘야 프로세스간 통신이 가능하다.

- 파이프 기반의 프로세스간 통신
```c
include <unistd.h>

int pipe(int filedes[2]);
```

- 멀티 프로세스 서버의 단점
    - 프로세스의 빈번한 생성은 성능의 전하로 이어진다.
    - 멀트 프로세스의 흐름을 고려해서 구현해야하기 때문에 구현이 쉽지 않다.
    - 프로세스간 통신이 필요한 상황에서는 서버의 구현이 더 복잡해진다.
- 멀티 프로세스 서버의 대안
    - 하나의 프로세스가 다수의 클라이언트에거 서비스를 할 수 있도록 한다.
    - 이를 위해서는 하나의 프로세스가 여러 개의 소켓을 핸들링 할 수 있는 방법이 존재 해야한다.
    - 이것이 **IO 멀티플랙싱**이다.

- select 함수의 기능과 호출순서
    1. Step 0ne - 관찰의 댕상을 묶고, 관찰의 유형을 지정한다.
        - 파일티스크리터의 설정
        - 검사의 범위 지정
        - 타임아웃의 설정
    2. Step two - 관찰 대상의 변화를 묻는다.
        - select 함수의 호출
    3. Step Three - 물음에 대한 대답을 듣는다.
        - 호출결과 확인

- fd_set 형 변수의 컨트롤 함수
    - FD_ZERO(fd_set * fdset) - 인자로 전달된 주소의 fd_set형 변수의 모든 비트를 0으로 초기화 한다.
    - FD_SET(int fd, fd_set *fdset) - 매개변수 fdset으로 전달된 주소의 변수에 매개변수 fd로 전달된 파일 디스크립터 정보를 등록한다.
    - FD_CLR(int fd, fd_set *fdset) - 매개변수로 fdset으로 전달된 주소의 변수에서 배개변수 fd로 전달된 파일 디스크립터 정보를 삭제한다.
    - FD_ISSET(int fd, fd_set *fdset) - 매개변수 fdset으로 전달된 주소의 변수에 매개변수 fd로 전달된 파일 디스크립터의 정보가 있으면 양수를 변환한다.

```c
#include <sys/select.h>
#include <sys/time.h>

int select(
    int maxfd, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeva * timeout);
)
```
    

## 5일차(2024-06-17)
- send 함수
```c
#include <sys/socket.h>

ssize_t send(int sockfd, const void * buf, size_t nbytes, int flags);
```

- recv 함수
```c
#include <sys/socket.h>

ssize_t recv(int sockfd, void * buf, size_t nbytes, int flags);
```
- MSG_OOB - 긴급 메시지의 전송

- writev 함수 - 둘 이상의 영역에 나뉘어 저장된 데이터를 묶어서 한번의 함수호출을 통해서 보낼 수 있다.
```c
#include <sys/uio.h>

ssize_t writev(int filedes, const struct iovec * iov, int iovcnt);
```

- readv 함수 - 단 한번의 함수호출을 통해서 입력되는 데이터를 둘 이상의 영역에 나눠서 저장이 가능하다.
```c
#include <sys/uio.h>

ssize_t readv(int filedes, const struct iovec * iov, int iovcnt);
```

- 표준 입출력 함수의 장점
    - 표준 입출력 함수는 이식성이 좋다.
    - 표준 입출력 함수는 버퍼링을 통한 성능의 향상에 도움이 된다.
- 표준 입출력 함수의 사용에 있어서 불편사항
    - 양방향 통신이 쉽지 않다.
    - 상황에 따라서 fflush함수의 호출이 빈번히 등장할 수 있다.
    - 파일 디스크립터를 FILE 구조체의 포인터로 변환해야 한다.
- fdopen함수
```c
#include <stdio.h>
FILE * fdopen(int fildes, const char *mode)
```
- fileno 함수
```c
#include <stdio.h>
int fileno(FILE * stream);
```

- 파일 디스크립터의 복사
```c
#include <unistd.h>

int dup(int fildes);
int dup2(int fildes, int fildes2);
```

## 6일차 (2024-06-18)
- 챕터 17부터~20까지
- select 기반의 IO 멀티플렉싱이 느린 이유

## 7일차 (2024-06-19)

- 리눅스서버에서 서버를 구현해서 윈도우에서 실행시켜보기