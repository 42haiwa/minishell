/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:39:00 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 13:45:35 by aallou-v         ###   ########.fr       */
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

typedef struct s_env
{
	char	*path;
	char 	*pwd;
	char	*old_pwd;
}	t_env;

typedef struct s_core
{
	struct s_env	*env;
}	t_core;

//	builtins.c
void	check_builtins(char const *buf);
//	exit.c
void	ft_exit(void);
//	cd.c
void	ft_cd(const char *path);
//	parse_envp.c
void	parse_envp(t_core *core, char **envp);

#endif
