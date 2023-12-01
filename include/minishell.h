/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:39:00 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 14:47:33 by aallou-v         ###   ########.fr       */
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

typedef struct s_three
{
	void			*content;
	struct s_three	*nodes;
}	t_three;

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
t_three	*three_init(void *content);
//void	*three_add(t_three **father, three *son);
char	*set_envp(char *getter, char *new_values, t_core *core);
char	*get_envp(char *getter, t_core *core);

#endif
