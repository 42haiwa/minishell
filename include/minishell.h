/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:39:00 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/10 20:15:44 by aallou-v         ###   ########.fr       */
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

# include "libft.h"

typedef struct s_node
{
	void			*content;
	ssize_t			sons_ctr;
	struct s_node	**sons;
}	t_node;

t_node	*node_init(void *content);
void	node_add_son(t_node *father, t_node *neww);
void	node_print_recurse(t_node *root);

typedef struct s_core
{
	char	**envp;
	char	*prompt;
	char	*folder;
	char	*lexer_out;
	t_node	*execution_three;
}	t_core;

//	builtins.c
int		check_builtins(char *buf, t_core *core);
//	exit.c
void	ft_exit(void);
//	cd.c
void	cd(const char *path, t_core *core);
//	parse_envp.c
void	parse_envp(t_core *core, char **envp);

//	three
t_node	*node_init(void *content);
void	node_add_son(t_node *father, t_node *neww);
void	node_print_recurse(t_node *root);

//	envp
char	*set_envp(char *getter, char *new_values, t_core *core);
char	*get_envp(char *getter, t_core *core);

//get_prompt
char	*get_prompt(t_core *core);
//lexing
void	lexing(char *buf, t_core *core);
void	pre_lexing(char *buf, t_core *core);

//parsing
void	rm_sep_three(t_node *node);
void	fill_three(t_core *core);
//execution
void	execution(t_core *core);
//utils
char	*add_char(const char *s, char c, int index);
//handler
void	handler(int sig);
//get_path
char	*ft_get_path(t_core *core, char *cmd);
//pwd
void	pwd(void);
//env
void	env(t_core *core);
#endif
