NAME := minishell

CFLAGS := -g -Wall -Wextra -Werror -Iinclude
LDFLAGS := -Llib -lft -lreadline

SRC := src/main.c \
		src/ft_close.c \
		src/node_init.c \
		src/parsing.c \
		src/parsing2.c \
		src/node_add_son.c \
		src/node_print_recurse.c \
		src/parse_envp.c \
		src/lexing.c \
		src/lexing2.c \
		src/execution.c \
		src/execution2.c \
		src/execution_utils.c \
		src/handler.c \
		src/utils.c \
		src/get_path.c \
		src/builtins/exit.c \
		src/builtins/cd.c \
		src/builtins/builtins.c \
		src/builtins/pwd.c \
		src/builtins/env.c \
		src/builtins/echo.c \
		src/builtins/export.c \
		src/parse_io.c \
		src/get_d_quote.c \
		src/get_quote.c \
		src/replace_env.c \
		src/builtins/unset.c \
		src/utils2.c
OBJ := $(SRC:.c=.o)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

all:		$(NAME)

clean:
			$(RM) -f $(OBJ)

fclean:		clean
			$(RM) -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

