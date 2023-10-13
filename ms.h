/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:31:53 by jteoh             #+#    #+#             */
/*   Updated: 2023/10/13 15:38:40 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>


typedef struct s_lexer{
	char			**test;
	struct s_list	*next;
}				t_lexer;

typedef struct s_input{
	char	**line;
}				t_input;

typedef struct s_env{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

//--main.c--
void		handle(char *line);
void		free2d(char **line);
void		ctrlc(int sig);
int			main(int argc, char **argv, char **envp);

//--env.c--
void		display_env(t_env *env);

//--echo.c--
int			hyphen(char *hy);
int			n(char *n);
void		echo(t_input *input);

//--call.c--
void		call(t_input *input);

#endif
