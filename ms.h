/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:31:53 by jteoh             #+#    #+#             */
/*   Updated: 2023/09/20 17:38:45 by jteoh            ###   ########.fr       */
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

typedef struct s_input{
	char	**line;
}				t_input;

typedef struct s_env{
	char	**envp;
}				t_env;

void		display_env(t_env *env);
void		call(t_input *input);
void		echo(t_input *input);
int			n(char *n);

#endif
