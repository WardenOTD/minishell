#include "ms.h"

char	*get_str_inquote(char *str, int info, int *pos)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = *pos;
	j = i;
	k = 0;
	while (str[i] && str[i] != info)
		i++;
	ret = malloc (sizeof(char) * (i - *pos + 1));
	while (j < i)
	{
		ret[k] = str[j];
		k++;
		j++;
	}
	ret[k] = 0;
	*pos = i + 1;
	return (ret);
}

char	*get_str_outquote(char *str, int *pos)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = *pos;
	j = i;
	k = 0;
	while (str[i] && str[i] != ' ' && str[i] != '|'
		&& str[i] != '<' && str[i] != '>')
		i++;
	ret = malloc (sizeof(char) * (i - *pos + 1));
	while (j < i)
	{
		ret[k] = str[j];
		k++;
		j++;
	}
	ret[k] = 0;
	*pos = i;
	return (ret);
}

char	*get_str_token(char *str, int *pos)
{
	int		i;
	char	*ret;

	i = *pos;
	ret = NULL;
	if (str[i] == '|')
		ret = strdup("|");
	else if (str[i] == '<' && str[i + 1] == '<')
		ret = strdup("<<");
	else if (str[i] == '<' && str[i + 1] != '<')
		ret = strdup("<");
	else if (str[i] == '>' && str[i + 1] == '>')
		ret = strdup(">>");
	else if (str[i] == '>' && str[i + 1] != '>')
		ret = strdup(">");
	*pos += strlen(ret);
	return (ret);
}

char	**splitter(char *str)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	ret = (char **) malloc (sizeof(char *) * 30);
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			ret[j] = get_str_token(str, &i);
			j++;
		}
		else if (str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
		{
			ret[j] = get_str_outquote(str, &i);
			j++;
		}
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i++;
			ret[j] = get_str_inquote(str, str[i - 1], &i);
			j++;
		}
		else
			i++;
	}
	ret[j] = 0;
	return (ret);
}

int		find_unclosed_quote(char *str)
{
	int	i;
	int	pendulum;
	char	type;

	i = 0;
	type = 0;
	pendulum = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && pendulum == 0)
		{
			type = str[i];
			pendulum = 1;
		}
		else if ((str[i] == '\"' || str[i] == '\'') && pendulum > 0)
			if (str[i] == type)
				pendulum = 0;
		i++;
	}
	return (pendulum);
}

char	***arr_arr_split(char **arr)
{
	int		i;
	int		j;
	int		pp_i;
	char	***ret;

	i = 0;
	j = 0;
	pp_i = 0;
	ret = (char ***) malloc (sizeof(char **) * 20);
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], "|", 2))
		{
			ret[pp_i] = arr_dup_n(arr, j, i);
			i++;
			j = i;
			pp_i++;
		}
		i++;
	}
	ret[pp_i] = arr_dup_n(arr, j, i);
	pp_i++;
	ret[pp_i] = 0;
	return (ret);
}
