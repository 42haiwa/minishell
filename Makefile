NAME := minishell

CFLAGS := -g -Wall -Wextra -Werror -Iinclude
LDFLAGS := -Llib -lft -lreadline

SRC := src/main.c \
		src/exit.c \
		src/cd.c \
		src/parse_envp.c
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
