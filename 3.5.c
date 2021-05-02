#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <math.h>

int main (void) {
	void sigint_handler( int sig );
	if( signal( SIGINT, sigint_handler ) == SIG_ERR ) {
		perror("signal");
		exit(1);
		}

	int pipefds[2];
	int buffer;
	pid_t pid = fork();
	int number, flag = 0;

	if(pipe(pipefds) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if(pid == 0) {
		printf("Pleas enter a number: ");
		scanf("%d", &number);
		close(pipefds[0]);
		write(pipefds[1], &number,sizeof(number));
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0) {
		wait(NULL);

		close(pipefds[1]);
		read(pipefds[0], &buffer, sizeof(buffer));
		close(pipefds[0]);

		int j = buffer / 2;
		for(int i = 2; i <= j; i++){
			if(buffer % i == 0) {
				printf("Number is not a prime\n");
				flag = 1;
				break;
			}
		}
		if(flag == 0)
			printf("Number is a prime\n");
	}
	else {
		perror("error");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

void sigint_handler (int sig) {
	printf("This is a special signal handler for INT signal\n");
}
