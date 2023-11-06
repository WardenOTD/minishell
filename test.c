#include "ms.h"
#include "libft/libft.h"
int	main()
{
	t_lexer *list;

	char	**arr;
	list = (t_lexer *)malloc(sizeof(t_lexer));
	arr = malloc(sizeof(char *) * 3);
	arr[0] = strdup("kjhgf");
	arr[1] = strdup("iuytre");
	arr[2] = 0;
	list->test = arr;
	printf("%s\n%s\n", list->test[0], list->test[1]);
	list->next = (t_lexer *)malloc(sizeof(t_lexer));
	list = list->next;
	list->test = arr;
	printf("%s\n%s\n", list->test[0], list->test[1]);
}
