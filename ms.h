/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:31:53 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/16 09:55:35 by jutong           ###   ########.fr       */
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
# include <errno.h>

typedef struct s_lexer{
	char			**arg;
	struct s_lexer	*next;
}				t_lexer;

typedef struct s_input{
	char	**line;
}				t_input;

typedef struct s_exp{
	char			*export;
	struct s_exp	*next;
}				t_exp;

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
t_exp		*explstnew(char *k, char *v);

//--env.c--
void		display_env(t_env *env);
t_env		*get_env(t_env *env, char **envp);
t_env		*add_env(t_env *env, t_lexer *input);
char 		*get_env_value(char *str, t_env *env);

//--export.c--
void		display_exp(t_exp *exp);
int			bubble_sort(char *str1, char *str2);
int			sort_check(t_exp *exp);
t_exp		*get_exp(t_exp *exp, t_env *env);
t_exp		*free_exp(t_exp *exp);

//--export2.c--
void		export_get(t_lexer *input, t_env *env, t_exp *exp);

//--lexer.c--
t_lexer		*lexer(t_lexer *input, char *line);
t_lexer		*freelexer(t_lexer *input);

//--echo.c--
int			hyphen(char *hy);
int			n(char *n);
void		echo(t_lexer *input);

//--call.c--
void		call(t_lexer *input, t_env *env, t_exp *exp, char *line, char **envp);

//--pwd.c--
int			ft_pwd(void);

//--cd.c--
int			cd(t_lexer *lexer, t_env *env);
char		*update_env(t_env *env, char *current, char *new);
void		add_oldpwd(t_lexer *lexer, t_env *env, char *oldpwd_str);

//--unset.c--
void		unset(t_lexer *lexer, t_env *env);
void		remove_node(t_env **env, char *remove);

//--bultin_cmd--
int			exec_bin(char *line, char **envp);
char		*append_path(char *cmdpath, char *input_line);
char		**get_env_paths(char **envp);
void		free_2d_arr(char **arr_2d);

//--utils.c--
int			get_arraysize(char **array);

#endif
