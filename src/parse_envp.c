/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:39:48 by aallou-v          #+#    #+#             */
/*   Updated: 2023/12/01 13:47:55 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_envp(t_core *core, char **envp)
{
	char	**values;
	int		i;

	values = envp;
	i = -1;
	while (values[++i])
	{
		if (ft_strncmp(values[i], "OLDPWD", 6) == 0)
			core->env->old_pwd = ft_strdup(ft_strchr(values[i], '/'));
		if (ft_strncmp(values[i], "PWD", 3) == 0)
			core->env->pwd = ft_strdup(ft_strchr(values[i], '/'));
		if (ft_strncmp(values[i], "PATH", 4) == 0)
			core->env->path = ft_strdup(ft_strchr(values[i], '/'));
	}
}
