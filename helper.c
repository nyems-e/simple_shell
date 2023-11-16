#include "main.h"

/**
 * func_free - free array
 * @Array: array
 * @tokCount: token Count
 */
void func_free(char **Array, size_t tokCount)
{
	size_t x;

	for (x = 0; x < tokCount; x++)
		free(Array[x]);
	free(Array);
}
