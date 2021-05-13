void handler_kill(int num)
{
	printf("%d\n", num);
	exit(0);
}

void handler_quit(int num)
{
	printf("Quit: %d\n", num);
	exit(0);
}