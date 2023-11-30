/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:39:00 by cjouenne          #+#    #+#             */
/*   Updated: 2023/11/30 20:14:27 by aallou-v         ###   ########.fr       */
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
	char 	*path;
	char 	*pwd;
	char	*old_pwd;
}	t_env;

//	builtins.c
void	check_builtins(char const *buf);
//	exit.c
void	ft_exit(void);
//	cd.c
void	ft_cd(const char *path);
//	parse_envp.c
void	parse_envp(char **envp, t_env *env);

#endif
