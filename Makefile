SRC			= main.c liststuff.c env.c export.c export2.c lexer.c expansion.c\
				call.c echo.c cd.c pwd.c split2.c unset.c utils.c\
				exec.c redirection.c redirection_utils.c redirection_func.c pipe_init.c\

CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
# FSANITIZE	= -fsanitize=address -g3
# DSYM		= && rm -rf *.dSYM

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
