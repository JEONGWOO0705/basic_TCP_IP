#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>



void timeout(int sig) {
	if (sig == SIGALRM)
		puts("Time out");
	alarm(2);
}
void keycountrol(int sig){
	if(sig == SIGINT)
		puts("CTRL + C pressed");
}

int main(int argc, char* argv[]) {
	
	int i;
	struct sigaction act;
	act.sa_handler = timeout;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, 0);

	alarm(2);
	for (i = 0; i < 3; i++) {
		puts("wait....");
		sleep(100);
	}
	return 0;
}
