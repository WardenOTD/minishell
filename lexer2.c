#include "ms.h"

// int main()
// {
// 	int i = 0;
// 	char *str = "wonk | wonk >> arara";
// 	char **arr = true_split(str);

// 	while(arr[i])
// 	{
// 		printf("%s\n", arr[i]);
// 		i++;
// 	}

// 	return 0;
// }

char **true_split(char *line)
{
	int		i;
	int		j;
	int		arr_i;
	int		token_len;
	char	**arr;

	i = 0;
	j = 0;
	arr_i = 0;
	token_len = 0;
	arr = (char **) malloc (sizeof (char *) * 100); //change
	while (line[i])
	{
		token_len = 0;
		if (identify_token(line, i))
		{
			token_len = ft_strlen(identify_token(line, i));
			arr[arr_i] = str_extract(line, j, i);
			arr_i++;
			j = i + token_len;
		}
		i += (1 + token_len);
	}
	arr[arr_i] = str_extract(line, j, i);
	arr[arr_i + 1] = 0;
	return (arr);
}

t_lexer *get_token_data(char *line, t_lexer *input)
{
	int		i;
	int		j;
//	char	**arr;

	i = 0;
	j = 0;
	input->tokens = (char **) malloc (sizeof (char *) * 100); //change
	while (line[i])
	{
		if (identify_token(line, i))
		{
			input->tokens[j] = (char *) malloc (sizeof(char) * (ft_strlen(identify_token(line, i) + 1)));
			input->tokens[j] = ft_strdup(identify_token(line, i));
			j++;
			if (ft_strlen(identify_token(line, i)) == 2)
				i++;
		}
		i++;
	}
	input->tokens[j] = 0;
//	input->tokens = arr;
//	free2d(arr);
	return (input);
}

char	*str_extract(char *str, int start, int end)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *) malloc (sizeof(char) * (end - start + 2));
	while (start < end)
	{
		ret[i] = str[start];
		start++;
		i++;
	}
	ret[i] = 0;
	return (ret);
}

// | is 1
// < is 2
// << is 3
// > is 4
// >> is 5
char	*identify_token(char *str, int pos)
{
	int i;

	i = pos;

	if (str[i] == '|')
		return ("|");
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return ("<<");
		return ("<");
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (">>");
		return (">");
	}
	return (NULL);
}