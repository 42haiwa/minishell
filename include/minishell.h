/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:39:00 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/16 16:52:42 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell $ "
# define PRINT_LEXER 1

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"

typedef struct s_node
{
	void			*content;
	ssize_t			sons_ctr;
	struct s_node	**sons;
	int				output_mode;
	int				heredoc_id;
	char			*input;
	char			*output;
}	t_node;

t_node	*node_init(void *content);
void	node_add_son(t_node *father, t_node *neww);
void	node_print_recurse(t_node *root);

typedef struct s_core
{
	char	**envp;
	char	*prompt;
	char	*folder;
	int		is_children;
	char	*lexer_out;
	int		son_pid;
	int		err_code;
	char	**get_d_quote;
	char	**get_quote;
	t_node	*execution_three;
}	t_core;

extern t_core	*g_core;

//	builtins.c
int		check_builtins(char *buf, char **argv, int argc, t_core *core);
void	ft_exit(int argc, char **argv);
void	pwd(void);
void	env(t_core *core);
void	echo(char **argv, int argc, t_core *core);
void	cd(char **argv, int argc, t_core *core);
void	export(char **argv, int argc, t_core *core);
void	unset(char **argv, int argc, t_core *core);
int		check_builtins_no_fork(char *buf, char **argv, int argc, t_core *core);
//	parse_envp.c
void	parse_envp(t_core *core, char **envp);

//	three
t_node	*node_init(void *content);
void	node_add_son(t_node *father, t_node *neww);
void	node_print_recurse(t_node *root);

//	envp
char	*set_envp(char *getter, char *new_values, t_core *core);
char	*get_envp(char *getter, t_core *core);
void	remove_envp(char *getter, t_core *core);
void	add_envp(char *getter, char *values, t_core *core);

//lexing
void	lexing(char *buf, t_core *core);
void	pre_lexing(char *buf, t_core *core);

//parsing
void	rm_sep_three(t_node *node);
void	fill_three(t_core *core);
void	free_three(t_core *core);
//execution
void	execution(t_core *core);
//utils
char	*add_char(const char *s, char c, int index);
//handler
void	handler(int sig);
//get_path
char	*ft_get_path(t_core *core, char *cmd);
//parse_io
void	parse_io(t_core *core);
//lexing2
char	**get_double_quote(char *buf, t_core *core);
//get_quote
char	**get_quote(char *buf);

char	*replace(char *s, char *old, char *new);
char	**exctract_env(const char *chaine);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strstr(char *str, char *to_find);

void	replace_main(t_core *core);
#endif
