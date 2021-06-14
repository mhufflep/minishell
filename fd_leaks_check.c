# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int fd = open(argv[1], O_RDONLY, 0);
		if (fd < 0)
		{
			printf("Cannot open file: %s\n", argv[1]);
		}
		else
		{
			printf("Closest free fd is: %d\n", fd);
			close(fd);	
		}
		return (0);
	}
	else
	{
		printf("You should pass filename to argv[1]\n");
	}
	return (0);
}