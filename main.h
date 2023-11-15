#ifndef Header
#define Header

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void commandLine_prompt(void);
char **read_Commandline(char *lineptr, ssize_t *bytes_read,
const char *delim, size_t *tokCount);
int runCommand(char *cmd, char **arrayTok, size_t tokCount);
char **createTokens(char *line, const char *delim, size_t *tokCount);
size_t countTokens(char *line, const char *delim);
ssize_t _getline(char **lineptr, ssize_t *bytes_read, int fd);
int check_path(char *path);
char *handlePath(char *cmd);


extern char **environ;
#endif
