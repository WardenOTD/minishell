/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:31:53 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/14 17:10:57 by jteoh            ###   ########.fr       */
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
	char			**arg;
	struct s_lexer	*next;
}				t_lexer;

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
char		**env_split(char *arr);

//--export.c--
void		display_exp(t_exp *exp);
int			bubble_sort(char *str1, char *str2);
int			sort_check(t_exp *exp);
t_exp		*get_exp(t_exp *exp, t_env *env);
t_exp		*free_exp(t_exp *exp);

//--export2.c--
void		export_get(t_lexer *input, t_env *env, t_exp *exp);
int			has_slash(char *arr);

//--lexer.c--
t_lexer		*lexer(t_lexer *input, char *line, t_env *env);
t_lexer		*freelexer(t_lexer *input);

t_lexer		*requote(t_lexer *input);
int			quote_count(char **arr);
char		**dArray_join(char **front, char **back);
char		*flatten_arr(char **arr);
char		*flatten_arr_w_space(char **arr);
char		**inArray_join(char	**arr);
t_lexer		*remove_quote(t_lexer *input);

//--echo.c--
int			hyphen(char *hy);
int			n(char *n);
void		echo(t_lexer *input);

//--call.c--
void		call(t_lexer *input, t_env *env, t_exp *exp);

//--pwd.c--
int			ft_pwd(void);

//--cd.c--
int			cd(t_lexer *lexer, t_env *env);
char		*update_env(t_env *env, char *current, char *new);

//--split2.c--
char		**split2(char const *s, char c);

//--expansion.c--
t_lexer		*expand(t_lexer *input, t_env *env);
char		*remove_exp(char *needle, char *haystack);
char		*add_exp(char *needle, char *haystack, char *val);
t_lexer		*reorder(t_lexer *input);

#endif
