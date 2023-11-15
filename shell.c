#include "shell.h"

/**
 * main - Entry point of the program.
 *
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE.
*/

int main(int ac, char **av)
{
	info_t inf[] = {INFO_INIT};
	int fd;

	fd = 2;
	asm ("mov %1, %0\n\t"
		 "add $3, %0" : "=r" (fd) : "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				printString(av[0]);
				printString(": 0: Can't open ");
				printString(av[1]);
				printChar('\n');
				printChar(BUF_FLUSH);
				exit(127);
			} return (EXIT_FAILURE);
		}
		inf->readfd = fd;
	}
	envList(inf);
	readHistory(inf);
	shellLoop(inf, av);
	return (EXIT_SUCCESS);
}
