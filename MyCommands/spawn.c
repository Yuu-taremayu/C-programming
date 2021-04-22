#include <stdio.h>
#include <stdlib.h>

/* for fork() and exec */
#include <unistd.h>

/* for wait() */
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <command> <arg>\n", argv[0]);
		exit(1);
	}
	
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "fork(2) failed\n");
		exit(1);
	}

	/* parent process */
	if (pid == 0) {
		execl(argv[1], argv[1], argv[2], NULL);
		perror(argv[1]);
		exit(99);
	}
	/* child process */
	else {
		int status;

		waitpid(pid, &status, 0);
		printf("child (PID=%d) finished; \n", pid);
		if (WIFEXITED(status)) {
			printf("exit, status=%d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status)) {
			printf("signal, sig=%d\n", WTERMSIG(status));
		}
		else {
			printf("abnormal exit\n");
		}
		exit(0);
	}
}
