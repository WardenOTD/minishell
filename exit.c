/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:26:28 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 16:12:41 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	exit_w_arg(t_root *root, char **arg)
{
	int	str;

	printf("exit\n");
	ghost_arg(arg, root);
	str = is_str_num(arg[1]);
	if (arg[2])
	{
		if (str == 1)
		{
			printf("Minishell: exit: too many arguments\n");
			g_status_code = 1;
			return (1);
		}
	}
	if (arg[1])
		exit_w_arg_helper(str, root, arg);
	return (0);
}

void	ghost_arg(char **arg, t_root *root)
{
	if (arg[1] == NULL)
	{
		free4(root);
		exit (0);
	}
}

void	exit_w_arg_helper(int str, t_root *root, char **arg)
{
	int	arg1;

	if (str == 0)
		printf("Minishell: exit: %s: numeric argument required\n", arg[1]);
	arg1 = ft_atoi(arg[1]) % 256;
	free4(root);
	if (str == 1)
	{
		system("leaks -q minishell");
		exit (arg1);
	}
	system("leaks -q minishell");
	exit (255);
}

int	is_str_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	free4(t_root *root)
{
	root->env = free_env(root->env);
	root->exp = free_exp(root->exp);
	root->input = freelexer(root->input);
	free(root->line);
}
