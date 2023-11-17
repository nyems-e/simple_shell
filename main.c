#include "main.h"




/**
 * main - main
 * Return:  1
 */
int main(void)
{
	char *lineptr = NULL;
	size_t tokCount = 0;
	char *delim = " \n";
	char **tokArray = NULL;
	ssize_t bytes_read = 0;
	char *cmd_path = NULL;

	while (1)
	{
		tokArray = read_Commandline(lineptr, &bytes_read, delim, &tokCount);
		if (tokArray == NULL)
			break;
		if (tokArray[0] == NULL)
		{
			free(tokArray);
			continue;
		}
		if (isBuiltin(tokArray, tokCount) == 1)
		{
			func_free(tokArray, tokCount);
			continue;
		}
		if (!(check_path(tokArray[0])))
		{
			cmd_path = handlePath(tokArray[0]);
			if (cmd_path != NULL)
			{
				runCommand(cmd_path, tokArray, tokCount);
				free(cmd_path);
			}
			else
			{
				func_free(tokArray, tokCount);
				perror("Command doesn't Exist");
			}
			continue;
		}
		runCommand(tokArray[0], tokArray, tokCount);
	}
	return (1);
}

