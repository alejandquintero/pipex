#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int	main()
{
	char *args[] = {"/bin/cat", "readme", NULL};
	int	fd;
	int	id;

	id = fork();
	if (id == 0){
		fd = open("results.txt", O_WRONLY, 0777);
		if (fd == -1){
			printf("Could not open the file\n");
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execv(args[0], args);
	}else{
		wait(NULL);
		printf("success!");
	}
	return (0);
}