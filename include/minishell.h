/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:03:18 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/22 18:08:16 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define QUOTE 0
# define D_QUOTE 1
# define BOTH 2
# define START 7
# define END 8
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

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
	int				outpipe;
}	t_node;

t_node	*node_init(void *content);
void	node_add_son(t_node *father, t_node *neww);
void	node_print_recurse(t_node *root);

typedef struct s_core
{
	char	**envp;
	char	*folder;
	int		is_children;
	char	*lexer_out;
	int		son_pid;
	int		err_code;
	char	**get_d_quote;
	char	**get_quote;
	char	*tmp;
	int		lex_n_quote;
	int		lex_n_d_quote;
	int		lex_bool[3];
	char	*lex_join;
	char	first;
	char	*substr;
	int		print_lex;
	int		boolean;
	size_t	lex_count;
	size_t	lex_count2;
	size_t	lex_i;
	size_t	lex_x;
	t_node	*execution_three;
}	t_core;

/***************
*              *
*              *
*  NORM STRUC  *
*              *
*              *
***************/

typedef struct s_d_quote
{
	size_t	var[2];
	int		boolean[2];
	size_t	double_quote_number;
}	t_d_quote;

typedef struct s_d_count
{
	size_t	i;
	size_t	count;
	int		boolean[2];
}	t_d_count;

typedef struct s_quote
{
	size_t	var[2];
	int		boolean[2];
	size_t	quote_number;
}	t_quote;

typedef struct s_count
{
	size_t	i;
	size_t	count;
	int		boolean[2];
}	t_count;

typedef struct s_parse
{
	int		i;
	int		j;
	int		fd;
	char	*buf;
	char	*tmp;
}	t_parse;

typedef struct s_repl
{
	size_t	i;
	size_t	j;
	size_t	occurence;
	size_t	val;
}	t_repl;

typedef struct s_exec
{
	int		pipe_fd[128][2];
	size_t	i;
	ssize_t	j;
	pid_t	c_pid;
	size_t	pipe_ctr;
	int		o_fd;
	int		i_fd;
	char	*check;
	size_t	cmd;
	char	*test;
	char	**new_argv;
}	t_exec;

int		check_exit(char const *s);
//	builtins.c
int		check_builtins(char *buf, char **argv, int argc, t_core *core);
void	ft_exit(int argc, char **argv, t_core *core);
void	pwd(t_core *core);
void	env(t_core *core);
void	echo(char **argv, int argc, t_core *core);
void	cd(char **argv, int argc, t_core *core);
void	export(char **argv, int argc, t_core *core);
void	unset(char **argv, int argc, t_core *core);
int		check_builtins_no_fork(char *buf, char **argv, int argc, t_core *core);
//	parse_envp.c
void	parse_envp(t_core *core, char **envp);
//main.c
void	free_str_tab(char **str_tab);
//	three
t_node	*node_init(void *content);
void	node_add_son(t_node *father, t_node *neww);
void	node_print_recurse(t_node *root);

//	envp
void	set_envp(char *getter, char *new_values, t_core *core);
char	*get_envp(char *getter, t_core *core);
void	remove_envp(char *getter, t_core *core);
void	add_envp(char *getter, char *values, t_core *core);

//lexing
void	lexing(char **splited, t_core *core);
void	pre_lexing(char *buf, t_core *core);
int		ft_check_end_quote(char *buf, t_core *core);

//parsing
void	rm_sep_three(t_node *node);
void	fill_three(t_core *core);
void	free_three(struct s_node **node);
void	verify_token(size_t *i, t_node **current,
			t_node **father, t_core *core);
void	verify_token2(size_t *i, t_node **current,
			t_node **father, t_core *core);
//execution
void	pre_execution(t_core *core);
void	execution(t_core *core);
//execution2
void	five_exec(t_core *core, t_exec *stru);
void	six_exec(t_core *core, t_exec *stru);
void	init_exec(t_exec *stru);
void	end_exec(t_core *core, t_exec *stru);
//execution_utils
int		is_token(char const *s);
int		check_builtins_no_exec(char *buf);
//utils
char	*add_char(char *s, char c, int index);
size_t	get_len(const char *s, int *index, const char c);
//void	add_char(char *s, char c, int index);
//handler
void	handler(int sig);
void	handler2(int sig, siginfo_t *info, void *ucontext);
//get_path
char	*ft_get_path(t_core *core, char *cmd);
//parse_io
void	parse_io(t_core *core);
//lexing2
char	**get_double_quote(char *buf);
char	*get_delimiter(char *token);
void	add_block(const char *s, t_core *core, int delimiter);
char	*init_lexing(t_core *core, char *buf);
//get_quote
char	**get_quote(char *buf);

char	*replace(char *s, char *old, char *new);
char	**exctract_env(const char *chaine);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strstr(char *str, char *to_find);

void	replace_main(t_core *core);

void	ft_close(int fd);
//utils2
int		is_ending(char c);
int		ft_strcmp(const char *s1, const char *s2);
int		get_n_char(const char *s1, char c);
char	*ft_strcspn(char* str, char *charset);
int		is_charset(char c, char *charset);
//utils3
char	*safe_join(char *s1, char *s2, int free_s1, int free_s2);
char	*get_substring(char *str, char c, int start_index);
char	*get_string(char *buf, char start, int index);
char	get_first(char *str, char *charset, size_t start);
char	*remove_char(char *str, int val);
//utils4
int		len_by_char(char *str, char c, size_t start);
int		ft_contain(char *str, int(*f)(char));
int		ft_contain_charset(char *str, char *c);
int		is_export_enable(char c);
//export_unset_utils
int		check_getter(char *getter);
//extra
char	*check_extra(char *buf);
#endif
