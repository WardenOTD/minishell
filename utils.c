#include "ms.h"

int get_arraysize(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**arr_dup_n(char **arr, int start, int end)
{
	char	**ret;
	int		i;

	i = 0;
	ret = (char **) malloc (sizeof(char *) * (end - start + 2));
	while (start < end)
	{
		ret[i] = ft_strdup(arr[start]);
		i++;
		start++;
	}
	ret[i] = NULL;
	return (ret);
}

int		is_token_str(char *str, int pos)
{
	if (str[pos] == '<' || str[pos] == '>')
	{
		if (str[pos + 1] == '<' || str[pos + 1] == '>')
			return (2);
		return (1);
	}
	else if (str[pos] == '|')
		return (1);
	return (0);
}

// char	*str_dup_n(char *str, int start, int end)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	while((start < end) && str[i])
// 	{
// 		ret[i] = str[start];
// 		i++;
// 		start++;
// 	}
// 	ret[i] = NULL;
// 	return (ret);
// }