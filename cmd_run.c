#include "main.h"

/**
 * runCommand - run commands
 * @cmd: command
 * @arrayTok: array of cmd arguments
 * @tokCount: token count
 * Return: 1
 */

int runCommand(char *cmd, char **arrayTok, size_t tokCount)
{
	int wstatus, status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error: Failure to fork parent process\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(cmd, arrayTok, environ) == -1)
		{
			perror("execve error: executable not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(&wstatus) == -1)
		{
			perror("Child process didn't terminate correctly\n");
			exit(EXIT_FAILURE);
		}
		if (isatty(STDIN_FILENO))
			func_free(arrayTok, tokCount);
		if WIFEXITED(wstatus)
			status = WEXITSTATUS(wstatus);
		return (status);
	}
	return (0);
}

