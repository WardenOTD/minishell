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

// char	*extend_str(char *str)
// {
// 	char	*ret;
// 	int		i;
// 	int		j;
// 	int		in_quote;

// 	i = 0;
// 	j = 0;
// 	in_quote = -1;
// 	ret = malloc (sizeof(char) * (ft_strlen(str) + 1));
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' || str[i] == '\'')
// 			in_quote *= -1;
// 		if (in_quote < 0 && is_token_str(str, i))
// 		{
// 			ret[j] = ' ';
// 			j++;
// 			ret[j] = str[i];
			
				
// 		}
// 		else
// 			ret[j] = str[i];
// 		i++;
// 		j++;
// 	}
// }

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
	ret = (char **) malloc (sizeof(char) * 50);
	while (arr[i])
	{
		tmp = recreate_str(arr[i]);
		if (tmp != NULL)
		{
			ret[j] = ft_strdup(tmp);
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

// char	**split_stuck_tokens(char **arr)
// {
// 	char	**ret;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	ret = (char **) malloc (sizeof(char) * 70);
// 	while (arr[i])
// 	{
// 		if (!ft_strncmp(arr[i], "|", 1) || !ft_strncmp(arr[i], "<", 1) ||!ft_strncmp(arr[i], ">", 1))
// 		{
// 			if (!ft_strncmp(arr[i], "<<", 2) || !ft_strncmp(arr[i], ">>", 2))
// 				ret[j] = str_dup_n(arr[i], 0, 2);
// 			else
// 				ret[j] = str_dup_n(arr[i], 0, 1);
// 			j++;
// 			if (!ft_strncmp(arr[i], "<<", 2) || !ft_strncmp(arr[i], ">>", 2))
// 				ret[j] = str_dup_n(arr[i], 2, ft_strlen(arr[i]));
// 			else
// 				ret[j] = str_dup_n(arr[i], 0, 1);
// 		}
// 		else
// 			ret[j] = ft_strdup(arr[i]);
// 		if (ret[j])
// 			j++;
// 		i++;
// 	}
// }

// t_lexer	*split_mods(char **arr, t_lexer *input)
// {
// 	int		i;
// 	int		j;
// 	char	**tmp;
// 	t_lexer	*temp;
// 	t_lexer	*tail;

// 	i = 0;
// 	j = 0;
// 	temp = NULL;
// 	tail = NULL;
// 	while (arr[i])
// 	{
// 		if (!ft_strncmp(arr[i], "|", 2) || arr[i + 1] == NULL)
// 		{
// 			tmp = arr_dup_n(arr, j, i);
// 			temp = lexerlstnew(tmp);
// 			free2d(tmp);
// 			if (!input)
// 				input = temp;
// 			else
// 				tail->next = temp;
// 			j = i + 1;
// 		}
// 		i++;
// 	}
// 	return (input);
// }

// int		find_unclosed_quote_mod(char *str)
// {
// 	int		i;
// 	int		value;
// 	char	**arr;

// 	i = 0;
// 	value = 0;
// 	arr = ft_split(str, '|');
// 	while (arr[i])
// 	{
// 		if (find_unclosed_quote(arr[i]) != 0)
// 			value = 1;
// 		i++;
// 	}
// 	free2d(arr);
// 	return (value);
// }

// char **split_arr_by_mod(char **args, int start)
// {
// 	int		i;
// 	int		max_len;
// 	char	**ret;

// 	i = start;
// 	max_len = start;
// 	while (args[i])
// 	{
// 		if (args[max_len] == NULL)
// 			break ;
// 		if (!ft_strncmp(args[i], "|", 2) && args[i])
// 			max_len = i;
// 		i++;
// 	}
// 	if (max_len == start)
// 		return (NULL);
// 	printf("test: %s\n", args[0]);
// 	ret = dup_arr_n_ele(args, start, max_len);
// 	return (ret);
// }

// char	**dup_arr_n_ele(char **arr, int start, int max)
// {
// 	int		i;
// 	char	**ret;

// 	i = start;
// 	ret = (char **) malloc (sizeof(char *) * (max - start + 2));
// 	while (i < max)
// 	{
		
// 		ret[i] = ft_strdup(arr[i]);
// 		i++;
// 	}
// 	ret[i] = 0;
// 	return (ret);
// }
