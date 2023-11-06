#include "ms.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	return (0);
}