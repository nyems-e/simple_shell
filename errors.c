#include "main.h"

/**
 * print_error - print error
 * @main_cmd: main cmd
 * @line_num: line number
 * @sh_cmd: shel cmd
 * Return: int
 */
int print_error(char *main_cmd, size_t line_num, char *sh_cmd)
{
	char *error_str = NULL;
	char line_num_str[1024];
	int error_size = 0;

	if (!isatty(STDIN_FILENO))
		error_size = (strlen(main_cmd) + (3 * strlen(": ")) + count_num(line_num)
			+ strlen(sh_cmd) + strlen("not found\n") + 1);
	else
		error_size = (strlen(main_cmd) + (3 * strlen(": ")) + count_num(line_num)
			+ strlen(sh_cmd) + strlen("command not found\n") + 1);

	error_str = malloc(error_size);
	if (error_str == NULL)
	{
		perror("print_error: malloc");
		exit(1);
	}
	intToAscii(line_num, line_num_str);
	strcpy(error_str, main_cmd);
	strcat(error_str, ": ");
	if (!isatty(STDIN_FILENO))
	{
		strcat(error_str,  line_num_str);
		strcat(error_str, ": ");
		strcat(error_str, sh_cmd);
		strcat(error_str, ": not found\n");
		strcat(error_str, "\0");
	}
	else
	{
		strcat(error_str, sh_cmd);
		strcat(error_str, ": command not found\n");
		strcat(error_str, "\0");
	}
	perror(error_str);
	free(error_str);
	return (1);
}


/**
 * intToAscii - integer to Ascii
 * @num: number
 * @string: string
 * Return: int
 */

int intToAscii(int num, char *string)
{
	int temp_dig = 0;
	int index = 0;
	int beg = 0;
	int end = 0;
	char temp_chr;

	if (num == 0)
	{
		string[0] = '0';
		string[1] = '\0';
		return (1);
	}
	while (num > 0)
	{
		temp_dig = num % 10;
		string[index++] = temp_dig  + '0';
		num /= 10;
	}
	end = index - 1;
	while (beg < end)
	{
		temp_chr = string[beg];
		string[beg] = string[end];
		string[end] = temp_chr;
		beg++;
		end--;
	}
	string[index] = '\0';
	return (1);
}


/**
 * count_num - count number
 * @line_num: line number
 * Return: int
 */
int count_num(size_t line_num)
{
	int count = 0;

	if (line_num == 0)
		return (1);
	while (line_num != 0)
	{
		line_num /= 10;
		count++;
	}
	return (count);
}

