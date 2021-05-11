#include "unistd.h"

int main(int ac, char **av, char **ep)
{
	execve(av[1], &av[0], ep);
	return (0);
}