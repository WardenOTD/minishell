SRC			= main.c main2.c\
				exit.c\
				sig_stuff.c\
				liststuff.c\
				env.c env2.c env3.c\
				export.c export2.c\
				unset.c\
				lexer.c lexer2.c lexer3.c lexer4.c\
				expansion.c expansion_helper.c expansion_helper_2.c\
				pipe_init.c pipe_init2.c\
				redirection.c redirection_utils.c redirection_func.c\
				call.c\
				exec.c exec2.c\
				echo.c\
				cd.c cd2.c\
				pwd.c\
				utils.c\

CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
FSANITIZE	= -fsanitize=address -g3
DSYM		= && rm -rf *.dSYM

RAED		= -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

LIBFT		= libft.a
NAME		= minishell


all:	${NAME}

${NAME}: ${LIBFT} ${SRC}
	${CC} ${CFLAGS} ${FSANITIZE} ${SRC} ${RAED} ${LIBFT} -o ${NAME} ${DSYM}

${LIBFT}:
	make -s all -C libft/
	mv libft/libft.a .

clean:
	@${RM} *.o
	make -s clean -C libft/

fclean: clean
	${RM} ${NAME} ${LIBFT}
	make -s fclean -C libft/

re: fclean all

.PHONY: all
