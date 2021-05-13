#include "unistd.h"
#include <stdio.h>

struct my_ptr {
	struct my_ptr *next, *prev;
};

struct my_node {
	struct my_ptr ptr;
	int a;
	char b;
};


void	uaccess(struct my_node *node)
{
	struct my_ptr ptr = *((struct my_ptr *)node);
	struct my_node n = *((struct my_node *)(ptr.next));
	printf("%d\n", (n.a));
}

int main(int ac, char **av, char **ep)
{
	struct my_node n1;
	struct my_node n2;

	n2.a = 5;
	n1.ptr.next = &(n2.ptr);
	uaccess(&n1);
	// execve(av[1], &av[0], ep);
	return (0);
}