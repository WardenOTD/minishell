/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:31:53 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 17:36:27 by jutong           ###   ########.fr       */
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

int	g_status_code;

typedef struct s_lexer
{
	char			**arg;
	struct s_lexer	*next;
}				t_lexer;

typedef struct s_exp
{
	char			*export;
	struct s_exp	*next;
}				t_exp;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_fd_info
{
	int				in_fd;
	int				out_fd;
	int				saved_in_fd;
	int				saved_out_fd;

	struct termios	new_attr;
	struct termios	saved_attr;
}				t_fd_info;

typedef struct s_pipe
{
	int		fd[2];
	pid_t	pid;
	int		fd_last[2];
	int		count;
	int		total_count;
}				t_pipe;

typedef struct s_root
{
	t_lexer	*input;
	t_env	*env;
	t_exp	*exp;
	char	**envp;
	char	**env_paths;
	int		has_pipe;
	t_pipe	pipe;
	char	*line;
}				t_root;

//--main.c--
void		free2d(char **line);
void		main_helper_1(char *line, t_root *root, t_fd_info *fd_info);
void		main_helper_2(t_root *root, t_fd_info *fd_info, char *line);
void		main_helper_3(pid_t pid);
int			main(int argc, char **argv, char **envp);

//--main2.c--
void		handle(char *line, t_env *env, t_fd_info *fd_info);
void		init(t_root *root, t_fd_info *fd_info);
void		init_2(t_root *root, t_fd_info *fd_info, char **envp);
void		ctrlc(int sig);
void		handle_ctrlc(t_fd_info *fd_info);

//--exit.c--
int			exit_w_arg(t_root *root, char **arg);
void		ghost_arg(char **arg, t_root *root);
void		exit_w_arg_helper(int str, t_root *root, char **arg);
int			is_str_num(char *arg);
void		free4(t_root *root);

//--sig_stuff.c--
void		ctrlslash(int sig);

//--liststuff.c--
t_lexer		*lexerlstnew(char **arr);
t_env		*envlstnew(char *k, char *v);
t_exp		*explstnew(char *k, char *v);
t_exp		*explstnew_helper(t_exp *head, char *k, char *v, int j);
t_exp		*explstnew_helper_helper(t_exp *head, int i);

//--env.c--
void		display_env(t_env *env);
t_env		*get_env(t_env *env, char **envp);
t_env		*add_env(t_env *env, char *arg);
t_env		*add_env_helper(t_env *env, t_env *tail, char **tmp);
char		*get_env_value(char *str, t_env *env);

//--env2.c--
char		**env_split(char *arr);
char		**env_split_helper(int i, char *arr, char **ret);
int			env_is_valid(char *str, t_env *env);
t_env		*free_env(t_env *env);
t_env		*shlvl(t_env *env);

//--env3.c
void		env_darr(t_root *root);
char		*env_arr(t_env *head);
int			envlist_len(t_env *env);

//--export.c--
void		display_exp(t_exp *exp);
int			sort_check(t_exp *exp);
int			bubble_sort(char *str1, char *str2);
t_exp		*get_exp(t_exp *exp, t_env *env);
t_exp		*free_exp(t_exp *exp);

//--export2.c--
void		export_get(t_lexer *input, t_env *env, t_exp *exp);
int			has_slash(char *arr);

//--unset.c--
void		unset(t_lexer *lexer, t_env *env);
void		remove_node(t_env **env, char *remove);
void		free_node(t_env *node);

//--lexer.c--
int			lexer(t_root *root, char *line, int segregation);
void		lexer_helper(t_root *root, char *line);
t_lexer		*freelexer(t_lexer *input);
int			find_unclosed_quote(char *str);

//--lexer2.c--
char		*create_str(char *str, int i, int j, int size);
char		*get_str_inquote(char *str, int info, int *pos);
char		*get_str_outquote(char *str, int *pos);
char		*get_str_token(char *str, int *pos);
char		**splitter(char *str);

//--lexer3.c--
char		***arr_arr_split(char **arr);
int			is_token(char c);
int			get_new_len(char *str);
int			get_new_len_helper(char *type, int *in_quote, char *str, int *i);
char		*remove_quote_helper(char *str);

//--lexer4.c--
char		*remove_quote_helper_2(char type, int in_quote,
				char *str, char *ret);
char		**remove_quotes(char **arr);
int			get_nor_arr_size(char *str);
int			get_tri_arr_size(char **arr);

//--expansion.c--
t_lexer		*expand(t_lexer *input, t_env *env);
char		*expand_helper_1(char *arg, t_env *env, int j);
int			yes_expand(char c1, char c2);
char		*replace_expand(char *str, char *to_r, t_env *env);
void		set_arr_to_zero(int *arr, int size);

//--expansion_helper.c--
char		*get_to_replace(char *str, int pos);
char		*get_new_value(char *to_r, t_env *env);
int			ft_strlen_checknull(char *str);
char		*replace_expand_helper(char *str, char *to_r,
				char *new_value, char *ret);

//--expansion_flags.c--
void		get_flag(int *flag, char c, int pos);
int			analyze_flag(int *flag);
int			analyze_flag_2(int *flag);

//--re_string.c--
char		*lexer_to_str(t_root *root);
char		*darr_to_arr_malloc(char **darr);
char		*darr_to_arr_copy(char **darr, char *arr, int space);
char		*append_w_pipe_malloc(char *str1, char *str2);
char		*append_w_pipe_copy(char *app, char *str1, char *str2);

//--pipe_init.c--
void		pipe_err(t_root *root, char *line);
void		pipe_var_init(t_root *root);
pid_t		pipe_init(t_root *root, char *line, t_fd_info *fd_info);
void		pipe_init_helper(t_lexer *head, t_root *root);
pid_t		pipe_init_helper_2(t_root *root, t_lexer *head, t_fd_info *fd_info);

//--pipe_init2.c--
void		cp_function(int count, int fd[2], int nig[2]);
int			invalid_pipe_front(char *str);
int			invalid_pipe_back(char *str);

//--redirection.c--
int			handle_redirect(char **args, t_fd_info *fd_info);
int			handle_redirect_helper(char *token_type,
				char **args, int token_pos);
int			do_redirections(char *token_type, char **args,
				int token_pos, t_fd_info *fd_info);
int			find_next_redir(char **args, int prev_i);
char		*identify_token(char *str);

//--redirection_utils.c--
int			check_first_arg(char **args);
char		**renew_arg_rm_redir(char **args);
int			invalid_redir(char *str);

//--redirection_func.c--
int			redir_output(char *filename, int out_fd);
int			redir_output_append(char *filename, int out_fd);
int			redir_input(char *filename, int in_fd);
int			redir_heredoc(char *delimiter, int in_fd);
int			redir_heredoc_helper(char *delimiter, int *pipe_fd);

//--call.c--
void		execute_cmd(t_root *root, t_lexer *input,
				char **envp, t_fd_info *fd_info);
void		call(t_root *root, t_lexer *input, char **envp);
int			call_builtins(t_root *root, t_lexer *input, char **envp);

//--exec.c--
int			exec_bin(t_root *root, t_lexer *input);
int			exec_bin_helper(t_root *root, char *path, int pidchild, char **arg);
int			exec_bin_parent(int pidchild, char **arg, char **env_paths);
char		*append_path(char *cmdpath, char *input_line);
char		**get_env_paths(t_env *env);

//--exec2.c--
char		**turn_arr_into_str(char **arr);

//--echo.c--
int			hyphen(char *hy);
int			n(char *n);
void		echo(t_lexer *input);

//--cd.c--
int			cd(t_lexer *lexer, t_env *env, char **envp);
char		*cd_detect_error(t_lexer *lexer, t_env *env,
				char *target_pwd, char *option);
char		*get_target_path(t_lexer *lexer, t_env *env,
				char **envp, char *option);
char		**get_target_pwd_helper(char **envp);
char		*update_env(t_env *env, char *current, char *neww);

//--cd2.c--
void		add_oldpwd(t_lexer *lexer, t_env *env, char *oldpwd_str);

//--pwd.c--
int			ft_pwd(void);

//--utils.c--
int			get_arraysize(char **array);
char		**arr_dup_n(char **arr, int start, int end);
char		*ft_strjoin_free(char *s1, char *s2);
void		error_msg(char *wrongcmd, char *msg);

#endif
