/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:25:00 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/08 12:23:58 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	handle(char *line, t_env *env, t_fd_info *fd_info)
{
	printf("exit\n");
	env = free_env(env);
	free(line);
	tcsetattr(STDIN_FILENO, TCSANOW, &fd_info->saved_attr);
	exit (0);
}

void	init(t_root *root, t_fd_info *fd_info)
{
	(root->env) = NULL;
	(root->input) = NULL;
	(root->exp) = NULL;
	fd_info->in_fd = 0;
	fd_info->out_fd = 1;
	fd_info->saved_in_fd = dup(STDIN_FILENO);
	fd_info->saved_out_fd = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &fd_info->saved_attr);
}

void	init_2(t_root *root, t_fd_info *fd_info, char **envp)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, SIG_IGN);
	init(root, fd_info);
	handle_ctrlc(fd_info);
	root->env = get_env(root->env, envp);
	env_darr(root);
}

void	ctrlc(int sig)
{
	signal(sig, SIG_IGN);
	rl_replace_line("", 0);
	write(0, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	signal(SIGINT, ctrlc);
}

void	handle_ctrlc(t_fd_info *fd_info)
{
	tcgetattr(STDIN_FILENO, &fd_info->new_attr);
	fd_info->new_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &fd_info->new_attr);
}
