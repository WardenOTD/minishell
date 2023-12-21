#include "ms.h"

int		find_unclosed_quote(char *str)
{
	int	i;
	int	pendulum;

	i = 0;
	pendulum = -1;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			pendulum *= -1;
		i++;
	}
	if (pendulum < 0)
		return (0);
	else
		return (pendulum);
}

char	*transform_str(char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		in_quote;

	i = 0;
	j = 0;
	in_quote = -1;
	ret = malloc (sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			in_quote *= -1;
		if (in_quote < 0 && str[i] == ' ')
			ret[j] = 7;
		else
			ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = 0;
	free(str);
	return (ret);
}

char	*recreate_str(char *str)
{
	char 	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			j++;
		i++;
	}
	if (j == 0)
		return (NULL);
	ret = malloc (sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		
		if (str[i] != '\"' && str[i] != '\'')
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
}

char	**recreate_arr(char **arr)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char **) malloc (sizeof(char) * 100);
	while (arr[i])
	{
		tmp = recreate_str(arr[i]);
		if (tmp != NULL)
		{
			ret[j] = ft_strdup(tmp);
			// printf("test: %s\n", ret[j]);
			free(tmp);
		}
		else
			ret[j] = ft_strdup("");
		j++;
		i++;
	}
	ret[j] = 0;
	free2d(arr);
	return (ret);
}
