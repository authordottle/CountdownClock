#include  <stdio.h>
#include  <signal.h>
#include <stdlib.h>

int main(int argc, char**argv) 
{
	if (argc != 2) {
		printf("argument number incorrect!\n");
		exit(1);
	}

	int pid = atoi(argv[1]);
	kill(pid, SIGUSR1);
}
