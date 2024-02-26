#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int	id;
	int	x;
	int	y;
	int	fds[2] = {0, 1};

	x = 0;
	if (pipe(fds) == -1)
		printf("An error ocurred calling pipe\n");
	id = fork();
	if (id == 0){
		close(fds[0]);
		printf("Type a number: ");
		scanf("%d", &x);
		write(fds[1], &x, sizeof(x));
		close(fds[1]);
	}else{
		wait(NULL);
		close(fds[1]);
		read(fds[0], &y, sizeof(y));
		printf("The number is: %d", y);
		close(fds[0]);
	}
	return (0);
}