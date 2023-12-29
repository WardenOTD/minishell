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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)ft_calloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1,
			sizeof(char));
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	while ((char)s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while ((char)s2[j] != '\0')
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*str_dup_n(char *str, int start, int end)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc (sizeof(char) * (end - start + 2));
	while((start < end) && str[i])
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = 0;
	return (ret);
}