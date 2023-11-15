#include "main.h"

/**
 * handlePath - find full path of a command
 * @cmd: command
 * Return: path to command
 */

char *handlePath(char *cmd)
{
	char *cmd_path, *cpy_path, *token;
	char *path_var = getenv("PATH");

	if (path_var == NULL) /*check if path variable exists*/
	{
		perror("PATH variable not found");
		return (NULL);
	}
	cpy_path = strdup(path_var); /* Duplicate the PATH variable for tokenization*/
	if (cpy_path == NULL)
	{
		perror("Error dupilcating path");
		return (NULL);
	}
	token = strtok(cpy_path, ":"); /* Tokenize the PATH variable using ':' */
	while (token != NULL)
	{
		cmd_path = malloc(strlen(token) + strlen(cmd) + 2);
		strcpy(cmd_path, token);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd);
		if (access(cmd_path, X_OK) == -1) /*validating path */
		{
			free(cmd_path);
			token = strtok(NULL, ":");
			continue;
		}
		free(cpy_path);
		return (cmd_path);
	}
		free(cpy_path);
		return (NULL);
}



/**
 * check_path - check if provided path contains a '/'
 * @path: path to check
 * Return: 1 0r 0
 */
int check_path(char *path)
{
	while (*path != '\0')
	{
		if (*path++ == '/')
		{
			return (1);
		}
		return (0);
	}
}

