#include "main.h"
/**
void commandLine_prompt(void)
{
	char *prompt = "$ ";
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, prompt, strlen(prompt));
	}
}


char **read_Commandline(char *lineptr, ssize_t *bytes_read, const char *delim, size_t *tokCount)
{
	*tokCount = 0;
	char **tokArray = NULL;
	commandLine_prompt();
	if (_getline(&lineptr, bytes_read, STDIN_FILENO) == -1)
	{
		perror("Error reading command line\n");
		free(lineptr);
		return(NULL);
	}	
	tokArray = createTokens(lineptr, delim, tokCount);
	free(lineptr);
	return (tokArray);
}



int runCommand(char *cmd, char **arrayTok, size_t tokCount)
{
	int wstatus, x;
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("Error: Failure to fork parent process\n");
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(cmd, arrayTok, NULL) == -1)
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
		for(x = 0; x < tokCount; x++)
			free(arrayTok[x]);
		free(arrayTok);
	}
	return (1);
}

		
	


size_t countTokens(char *line, const char *delim)
{
	size_t  tokCount = 0;
	char *tok = NULL;
	char *lineCpy = NULL;
	lineCpy = strdup(line);
	if (lineCpy == NULL)
	{
		perror("Error duplicating string in countTokens");
		return (-1);
	}
	tok = strtok(lineCpy, delim);
	while (tok != NULL)
	{
		++tokCount;
		tok = strtok(NULL, delim);
	}
	free(lineCpy);
	return (tokCount);
}

char **createTokens(char *line, const char *delim, size_t *tokCount)
{
	char *lineCpy = NULL, *token = NULL;
	unsigned int i = 0, x = 0;
	char **storeTokens = NULL;
	*tokCount = countTokens(line, delim);
	lineCpy = strdup(line);
	if (lineCpy == NULL)
        {
                perror("Error duplicating string in countTokens");
                return (NULL);
        }
	storeTokens = malloc(sizeof(char *) * (*tokCount + 1));
	if (storeTokens == NULL)
	{
		perror("Error allocating memory for token array");
		return (NULL);
	}		
	token = strtok(lineCpy, delim);
	for (i = 0; i < *tokCount; i++)
	{
		storeTokens[i] = strdup(token);
		if (storeTokens[i] == NULL)
		{
			for(x = 0; x < i; x++)
				free(storeTokens[x]);
			free(storeTokens);
			free(lineCpy);
			perror("Error allocating memory for tokens in createTokens");
			return(NULL);
		}
		token = strtok(NULL, delim);
	}
	free(lineCpy);
	storeTokens[*tokCount] = NULL;
	return (storeTokens);
}







ssize_t _getline(char **lineptr, ssize_t *bytes_read, int fd)
{
	size_t lineptr_Len = 0;
	char temp_buf[128];
	if (lineptr == NULL || bytes_read == NULL)
	{
		perror("Error: Incorrect argumnents to getline");	
		return (-1);
	}
	if (*lineptr == NULL)
	{
		*lineptr = (char *)malloc(sizeof(temp_buf));
		if (*lineptr == NULL)
		{
			perror("Memory allocation error in getline function");
			return (-1);
		}
		(*lineptr)[0] = '\0';
		*bytes_read = read(fd, temp_buf, sizeof(temp_buf));
		while (*bytes_read > 0)
		{
	       		lineptr_Len += *bytes_read;
			if (lineptr_Len - strlen(*lineptr) < sizeof(temp_buf))
			{
				*lineptr = (char *)realloc(*lineptr, lineptr_Len + 1);
				if (*lineptr == NULL)
				{
					perror("Reallocation of memory failed");
					free(*lineptr);
					return (-1);
				}
			}
			strncat(*lineptr, temp_buf, *bytes_read);	
			if (temp_buf[*bytes_read - 1] == '\n')
			{
				return (lineptr_Len - 1);
			}	
			memset(temp_buf, '\0', sizeof(temp_buf));
			*bytes_read = read(fd, temp_buf, sizeof(temp_buf));
		}
	}	
	return (-1);
}

char *handlePath(char *cmd){
	char *cmd_path, *cpy_path ,*token;
	char *path_var = getenv("PATH");
	if (path_var == NULL)
	{
		perror("PATH variable not found");
		return (NULL);
	}
	cpy_path = strdup(path_var);
	if (cpy_path == NULL)
	{
		perror("Error dupilcating path");
		return (NULL);
	}
	token = strtok(cpy_path, ":");
	while (token != NULL)
	{
		cmd_path = malloc(strlen(token) + strlen(cmd) + 2);
		strcpy(cmd_path, token);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd);
		if (access(cmd_path, X_OK) == -1) 
		{
			free(cmd_path);
			token = strtok(NULL,":");
			continue;
		}
		free(cpy_path);
		return (cmd_path);
	}
		free(cpy_path);
		return (NULL);
}

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
		{
			break;
		}
	      //printf("command: %s\ncount: %zu",tokArray[0], tokCount);
	      	if (!(check_path(tokArray[0])))	
		{
			//printf("%s\n%s\n", tokArray[0], tokArray[1]);
			if ((cmd_path = handlePath(tokArray[0])) != NULL)
			{
				//printf("%s\n", cmd_path);
				runCommand(cmd_path, tokArray, tokCount);
				free(cmd_path);
			}
			continue;
		}
		if (access(tokArray[0], F_OK) == -1)
		{
			printf("Command doesn't exist\n");
			continue;
		}	
		runCommand(tokArray[0], tokArray, tokCount);
	} 
	/**
	char *test = NULL;
	ssize_t br = 0;
	_getline(&test, &br, STDIN_FILENO);
	//getline(&test, &br, stdin);
	//char *test = "/bin/ls\n";
	//printf("Test: %s", test);
	char *delim = " \n";
	size_t tok = 0;
	char **arr = NULL;
	arr = createTokens(test, delim, &tok);
	printf("Tokcount: %zu\nTok1: %s\nTok2: %s\n", tok, arr[0], arr[1]);
	runCommand(arr[0], arr, tok); 
	
	return (1);  **/
}
