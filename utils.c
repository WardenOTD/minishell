#include "ms.h"

int get_arraysize(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*
char **array_dupe(char **arr_og)
{
	char **
}
*/