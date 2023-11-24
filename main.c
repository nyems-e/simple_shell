#include "main.h"



/**
 * main - main
 * @argc: argc
 * @argv: argv
 * Return: 1
 */
int main(__attribute((unused)) int argc, char *argv[])
{
	char *lineptr = NULL;
	size_t tokCount = 0;
	size_t line_num = 0;
	char *delim = " \n";
	char **tokArray = NULL;
	ssize_t bytes_read = 0;
	int status = 0;

	while (1)
	{
		line_num++;
		tokArray = read_Commandline(lineptr, &bytes_read, delim,
				&tokCount, status);
		if (!isatty(STDIN_FILENO))
		{
			nonInter_run(tokArray, tokCount, argv[0], line_num, &status);
			continue;
		}
		if (tokArray[0] == NULL)
		{
			free(tokArray);
			status = 0;
			continue;
		}
		if (isBuiltin(tokArray, tokCount) == 1)
		{
			func_free(tokArray, tokCount);
			continue;
		}
		if (main_helper(tokArray, tokCount, line_num, argv[0], &status) == 1)
			continue;
		status = runCommand(tokArray[0], tokArray, tokCount);
		if (status != 0)
			exit(status);
	}
	return (0);
}


/**
 * main_helper - check paths
 * @tokArray: token array
 * @tokCount: token count
 * @line_num: line number
 * @argv: argv
 * @status: exit code
 * Return: int
 */

int main_helper(char **tokArray, size_t tokCount, size_t line_num, char *argv,
		int *status)
{
	char *cmd_path = NULL;

	if (!(check_path(tokArray[0])))
	{
		cmd_path = handlePath(tokArray[0]);
		if (cmd_path != NULL)
		{
			*status = runCommand(cmd_path, tokArray, tokCount);
			free(cmd_path);
		}
		else
		{
			*status = print_error(argv, line_num, tokArray[0]);
			func_free(tokArray, tokCount);
		}
		return (1);
	}
	else if (access(tokArray[0], F_OK) == -1)
	{
		*status = print_error(argv, line_num, tokArray[0]);
		func_free(tokArray, tokCount);
		return (1);
	}
	return (0);
}

