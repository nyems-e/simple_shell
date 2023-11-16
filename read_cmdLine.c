#include "main.h"


/**
 * _getline - custom getline function
 * @lineptr: command line values
 * @bytes_read: bytes read per call
 * @fd: file descriptor
 * Return: total bytes read
 */
ssize_t _getline(char **lineptr, ssize_t *bytes_read, int fd)
{
	char temp_buf[128];
	size_t lineptr_Len = 0;

	if (*lineptr == NULL)
	{
		*lineptr = (char *)malloc(sizeof(temp_buf));
		if (*lineptr == NULL)
		{
			perror("Memory allocation error in getline function");
			exit(1);
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
					exit(1);
				}
			}
			strncat(*lineptr, temp_buf, *bytes_read);
			if (temp_buf[*bytes_read - 1] == '\n')
				return (lineptr_Len - 1);
			memset(temp_buf, '\0', sizeof(temp_buf));
			*bytes_read = read(fd, temp_buf, sizeof(temp_buf));
		}
	}
	if (isatty(STDIN_FILENO))
		return (-1);
	else
		return (1);
}


/**
 * createTokens - create an array of command line values
 * @line: cmd line values
 * @delim: delimiter
 * @tokCount: token count
 * Return: array of tokens
 */
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
			for (x = 0; x < i; x++)
				free(storeTokens[x]);
			free(storeTokens);
			free(lineCpy);
			perror("Error allocating memory for tokens in createTokens");
			return (NULL);
		}
		token = strtok(NULL, delim);
	}
	free(lineCpy);
	storeTokens[*tokCount] = NULL;
	return (storeTokens);
}



/**
 * countTokens - count tokens to be created
 * @line: cmd line values
 * @delim: delimiter
 * Return: token count
 */
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


/**
 * read_commandline - combining all funcs to read cmd line
 * @lineptr: command line values
 * @bytes_read: bytes read
 * @delim: delimiter
 * @tokCount: token Count
 * Return: array of tokens
 */
char **read_Commandline(char *lineptr, ssize_t *bytes_read,
const char *delim, size_t *tokCount)
{
	char **tokArray = NULL;
	ssize_t bRead = 0;
	*tokCount = 0;
	commandLine_prompt();
	bRead = _getline(&lineptr, bytes_read, STDIN_FILENO);
	if (bRead == -1)
	{
		perror("End of line\n");
		free(lineptr);
		return (NULL);
	}
	if (bRead == 1)
	{
		perror("\n");
		free(lineptr);
		exit(1);
	}

	tokArray = createTokens(lineptr, delim, tokCount);
	free(lineptr);
	return (tokArray);
}

/**
 * commandLine_prompt - send a prompt for shell
 */
void commandLine_prompt(void)
{
	char *prompt = "$ ";

	if (isatty(STDIN_FILENO))
	{
	write(STDOUT_FILENO, prompt, strlen(prompt));
	}
}

