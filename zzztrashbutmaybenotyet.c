#include "ms.h"

// t_lexer *get_token_data(char *line, t_lexer *input)
// {
// 	int		i;
// 	int		j;
// //	char	**arr;

// 	i = 0;
// 	j = 0;
// 	input->tokens = (char **) malloc (sizeof (char *) * 100); //change
// 	while (line[i])
// 	{
// 		if (identify_token(line))
// 		{
// 			input->tokens[j] = (char *) malloc (sizeof(char) * (ft_strlen(identify_token(line, i) + 1)));
// 			input->tokens[j] = ft_strdup(identify_token(line, i));
// 			j++;
// 			if (ft_strlen(identify_token(line, i)) == 2)
// 				i++;
// 		}
// 		i++;
// 	}
// 	input->tokens[j] = 0;
// //	input->tokens = arr;
// //	free2d(arr);
// 	return (input);
// }



// // | is 1
// // < is 2
// // << is 3
// // > is 4
// // >> is 5

// // int main()
// // {
// // 	int i = 0;
// // 	char *str = "wonk | wonk >> arara";
// // 	char **arr = true_split(str);

// // 	while(arr[i])
// // 	{
// // 		printf("%s\n", arr[i]);
// // 		i++;
// // 	}

// // 	return 0;
// // }

// char	**true_split(char *str)
// {
// 	char	**ret;
// 	int		i;
// 	int		i_a;
// 	int		end;
// 	int		in_quote;

// 	i = 0;
// 	i_a = 0;
// 	end = 0;
// 	in_quote = -1;
// 	ret = (char **) malloc (sizeof (char *));
// 	while (str[i])
// 	{
// 		while (str[i] == '\"' || str[i] == '\'' || (in_quote < 0 && str[i] == ' '))
// 		{
// 			if (str[i] == '\"' || str[i] == '\'')
// 				in_quote *= -1;
// 			i++;
// 		}
// 		end = str_findendpos(str, i, in_quote);
// 		ret[i_a] = str_extract(str, i, end);
// 		if (ret[i_a] != NULL)
// 			i_a++;
// 		i += end;
// 	}
// 	ret[i_a] = 0;
// 	return(ret);
// }

// int		str_findendpos(char *str, int start_pos, int in_quote)
// {
// 	int		end_pos;

// 	end_pos = start_pos;
// 	while (str[end_pos])
// 	{
// 		if ((str[end_pos] == ' ' || str[end_pos] == '\"' || str[end_pos] == '\'') && in_quote < 0)
// 		{
// 			if (str[end_pos] == '\"' || str[end_pos] == '\'')
// 				end_pos--;
// 			break ;
// 		}
// 		end_pos++;
// 	}
// 	return (end_pos);
// }

// char	*str_extract(char *str, int start, int end)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	ret =  malloc (sizeof(char) * (end - start + 1));
// 	while (start < end)
// 	{
// 		ret[i] = str[start];
// 		start++;
// 		i++;
// 	}
// 	ret[i] = 0;
// 	return (ret);
// }
