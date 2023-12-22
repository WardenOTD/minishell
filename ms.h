/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:31:53 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/22 10:31:06 by jteoh            ###   ########.fr       */
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


extern int	g_status_code;

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

typedef struct s_fd_info{
	int				in_fd;
	int				out_fd;
	int				saved_in_fd;
	int				saved_out_fd;

	struct termios	term_attr;

}				t_fd_info;

typedef struct s_root{
	t_lexer	*input;
	t_env	*env;
	t_exp	*exp;
}				t_root;

// typedef struct s_data{
// 	t_lexer			*input;
// 	t_env			*env;
// 	t_exp			*exp;
// 	int				in_fd;
// 	int				out_fd;
// }				t_data;

//--main.c--
void		handle(char *line);
void		free2d(char **line);
void		ctrlc(int sig);
//int			main(int argc, char **argv, char **envp);

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
int			env_is_valid(char *str, t_env *env);

//--export.c--
void		display_exp(t_exp *exp);
int			bubble_sort(char *str1, char *str2);
int			sort_check(t_exp *exp);
t_exp		*get_exp(t_exp *exp, t_env *env);
t_exp		*free_exp(t_exp *exp);

//--export2.c--
void		export_get(t_lexer *input, t_env *env, t_exp *exp);
int			has_slash(char *arr);

//--lexer.c & lexer_mine.c--
t_lexer		*lexer(t_lexer *input, char *line, t_env *env);
t_lexer		*freelexer(t_lexer *input);
int			find_unclosed_quote(char *str);
char		*transform_str(char *str);
char		*recreate_str(char *str);
char		**recreate_arr(char **arr);

//--lexer.c (unused)--
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
void		execute_cmd(t_root *root, t_lexer *input, char **envp, t_fd_info *fd_info);
void		call(t_root *root, t_lexer *input, char **envp);
int			call_builtins(t_root *root, t_lexer *input, char **envp);

//--pwd.c--
int			ft_pwd(void);

//--cd.c--
int			cd(t_lexer *lexer, t_env *env, char **envp);
char		*get_target_path(t_lexer *lexer, t_env *env, char **envp, char *option);
char		*cd_detect_error(t_lexer *lexer, t_env *env, char *target_pwd, char *option);
char		*update_env(t_env *env, char *current, char *new);
void		add_oldpwd(t_lexer *lexer, t_env *env, char *oldpwd_str);

//--unset.c--
void		unset(t_lexer *lexer, t_env *env);
void		remove_node(t_env **env, char *remove);
void		free_node(t_env *node);

//--bultin_cmd--
int			exec_bin(t_lexer *input, char **envp);
int			exec_bin_parent(int pidChild, char *line, char **arg, char **env_paths);
char		*append_path(char *cmdpath, char *input_line);
char		**get_env_paths(char **envp);
char		*turn_arr_into_str(char **arr);

//--utils.c--
int			get_arraysize(char **array);

//--split2.c--
char		**split2(char const *s, char c);

//--expansion.c--
t_lexer		*expand(t_lexer *input, t_env *env);
char		*remove_exp(char *needle, char *haystack);
char		*add_exp(char *needle, char *haystack, char *val);
t_lexer		*reorder(t_lexer *input);

//--redirection.c--
int			handle_redirect(char **args, t_fd_info* fd_info);
int			do_redirections(char *token_type, char **args, int token_pos, t_fd_info* fd_info);
int			find_next_redir(char **args, int prev_i);
char		*identify_token(char *str);

char		**renew_arg_rm_redir(char **args);

int			redir_output(char *filename, int out_fd);
int			redir_output_append(char *filename, int out_fd);
int			redir_input(char *filename, int in_fd);
int			redir_heredoc(char *delimiter, int in_fd);
int			redir_heredoc_helper(char *delimiter, int *pipe_fd);

//--pipe_init.c--
pid_t		pipe_init(t_root *root, char *line, char **envp, t_fd_info *fd_info);
void		pipe_err(t_root *root, char *line);
void		cp_function(int count, int fd[2], int nig[2]);

//--to trash--
char		**true_split(char *line);
char		*str_extract(char *str, int start, int end);
t_lexer 	*get_token_data(char *line, t_lexer *input);

#endif
