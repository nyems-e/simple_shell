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
const char *delim, size_t *tokCount, int status);
int runCommand(char *cmd, char **arrayTok, size_t tokCount);
char **createTokens(char *line, const char *delim, size_t *tokCount);
size_t countTokens(char *line, const char *delim);
ssize_t _getline(char **lineptr, ssize_t *bytes_read, int fd);
int check_path(char *path);
char *handlePath(char *cmd);
void b_exit(const char *status, char **cmd, size_t tokCount);
int b_env(void);
int isBuiltin(char **command, size_t tokCount);
void func_free(char **Array, size_t tokCount);
int print_error(char *main_cmd, size_t line_num, char *sh_cmd);
int intToAscii(int num, char *string);
int count_num(size_t line_num);
int main_helper(char **tokArray, size_t tokCount, size_t line_num, 
		char *argv, int *status);
int nonInter_run(char **tokArray, size_t tokCount, char *argv, 
		size_t line_num, int *status);
size_t check_Array(char **tokArray);


extern char **environ;
#endif

