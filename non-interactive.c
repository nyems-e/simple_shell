#include "main.h"

/**
 * check_Array - check number of times cmd repeats
 * @tokArray: token array
 * Return: size_t
 */
size_t check_Array(char **tokArray)
{
	int i;
	size_t count = 1;

	for (i = 0; tokArray[i + 1] != NULL; i++)
	{
		if (strcmp(tokArray[0], tokArray[i + 1]) == 0)
			count++;
	}
	return (count);
}

/**
 * nonInter_run - handle non-interactive section
 * @tokArray: token Array
 * @tokCount: token count
 * @argv: argv
 * @line_num: line number
 * @status: exit code
 * Return: int
 */
int nonInter_run(char **tokArray, size_t tokCount, char *argv,
		size_t line_num, int *status)
{
	size_t count = check_Array(tokArray);
	size_t i = 0;
	char *custom_arr[2];

	while (i < count)
	{
		i++;
		if (isBuiltin(tokArray, tokCount) == 1)
		{
			func_free(tokArray, tokCount);
			continue;
		}
		if (main_helper(tokArray, tokCount, line_num, argv, status) == 1)
			continue;
		if (count > 1)
		{
			custom_arr[0] = tokArray[0];
			custom_arr[1] = NULL;
			*status = runCommand(tokArray[i - 1], custom_arr, tokCount);
		}
		else
			*status = runCommand(tokArray[i - 1], tokArray, tokCount);
		if (*status != 0)
		{
			func_free(tokArray, tokCount);
			exit(*status);
		}
	}
	func_free(tokArray, tokCount);
	return (1);
}

