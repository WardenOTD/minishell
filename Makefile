SRC			= main.c \

CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -I.
FSANITIZE	= -fsanitize=thread -g3
DSYM		= *.dSYM

RAED		= -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

LIBFT		= libft.a
NAME		= minishell


all:	${NAME}

${NAME}: ${LIBFT} ${SRC}
	${CC} ${CFLAGS} ${FSANITIZE} ${SRC} ${RAED} ${LIBFT} -o ${NAME} && ${RM} ${DSYM}

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
