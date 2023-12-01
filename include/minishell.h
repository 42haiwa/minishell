/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:39:00 by cjouenne          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/01 15:26:25 by cjouenne         ###   ########.fr       */
=======
/*   Updated: 2023/12/01 14:47:33 by aallou-v         ###   ########.fr       */
>>>>>>> 4fd51051ba587b8b88fd6a129797d95f6e3638e1
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell $ "

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
}	t_core;

//	builtins.c
void	check_builtins(char const *buf);
//	exit.c
void	ft_exit(void);
//	cd.c
void	ft_cd(const char *path);
//	parse_envp.c
void	parse_envp(t_core *core, char **envp);

//	three
<<<<<<< HEAD
t_node	*node_init(void *content);
void	node_add_son(t_node *father, t_node *neww);
void	node_print_recurse(t_node *root);
=======
t_three	*three_init(void *content);
//void	*three_add(t_three **father, three *son);
char	*set_envp(char *getter, char *new_values, t_core *core);
char	*get_envp(char *getter, t_core *core);

>>>>>>> 4fd51051ba587b8b88fd6a129797d95f6e3638e1
#endif
