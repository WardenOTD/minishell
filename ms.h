/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:31:53 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/07 14:43:00 by jteoh            ###   ########.fr       */
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

typedef struct s_commandtable{
	char					**cmd;

	int						in_fd;
	int						out_fd;

//	struct s_env			t_env;

	struct s_commandtable	*next;
}				t_commandtable;

typedef struct s_lexer{
	char			**arg;
	int				var_num;
	struct s_lexer	*next;
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

//--liststuff.c--
t_lexer		*lexerlstnew(char **arr);
t_env		*envlstnew(char *k, char *v);

//--env.c--
void		display_env(t_env *env);
t_env		*get_env(t_env *env, char **envp);
char 		*get_env_value(char *str, t_env *env);
char		*update_env(t_env *env, char *current, char *new);

//--lexer.c--
t_lexer		*lexer(t_lexer *input, char *line);
t_lexer		*freelexer(t_lexer *input);

//--echo.c--
int			hyphen(char *hy);
int			n(char *n);
void		echo(t_lexer *input);

//--call.c--
void		call(t_lexer *input, t_env *env);
int			ft_pwd(void);
int			cd(t_lexer *lexer, t_env *env);

//--set aside--
int			parser(t_lexer *lexer);

#endif
