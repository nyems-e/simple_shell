#include "main.h"

/**
 * b_exit - exit
 * @status: arg for exit
 * @cmd: command
 * @tokCount: token count
 * Return: int
 */
void b_exit(const char *status, char **cmd, size_t tokCount)
{
	int s;

	if (status == NULL)
	{
		func_free(cmd, tokCount);
		exit(0);
	}
	else
	{
		s = atoi(status);
		func_free(cmd, tokCount);
		exit(s);
	}
}

/**
 * b_env - env
 * Return: int
 */

int b_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (1);
}


/**
 * isBuiltin - check for builtin cmd
 * @command: command
 * @tokCount: token count
 * Return: int
 */
int isBuiltin(char **command, size_t tokCount)
{
	if (strcmp(command[0], "env") == 0)
	{
		return (b_env());
	}
	else if (strcmp(command[0], "exit") == 0)
	{
		b_exit(command[1], command, tokCount);
	}
	return (0);
}


