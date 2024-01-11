NAME := minishell

CFLAGS := -g -Wall -Wextra -Werror -Iinclude
LDFLAGS := -Llib -lft -lreadline

SRC := src/main.c \
		src/node_init.c \
		src/parsing.c \
		src/node_add_son.c \
		src/node_print_recurse.c \
		src/parse_envp.c \
		src/get_prompt.c \
		src/lexing.c \
		src/execution.c \
		src/handler.c \
		src/utils.c \
		src/get_path.c \
		src/builtins/exit.c \
		src/builtins/cd.c \
		src/builtins/builtins.c \
		src/builtins/pwd.c \
		src/builtins/env.c \
		src/builtins/echo.c \
		src/parse_io.c
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

