/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:39:48 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/14 13:59:56 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_envp(char *getter, char *new_values, t_core *core)
{
	int	i;
	char	*values;

	i = -1;
	values = "";
	while (core->envp[++i])
	{
		if (ft_strncmp(getter, core->envp[i], ft_strlen(getter)) == 0)
		{
			values = ft_strjoin(getter, "=");
			values = ft_strjoin(values, new_values);
			if (!values)
				return (NULL);
			core->envp[i] = ft_strdup(values);
		}
	}
	return (new_values);
}

char	*get_envp(char *getter, t_core *core)
{
	int		i;
	char	*values;

	i = -1;
	values = "";
	if (ft_strncmp(getter, "\0", 1) == 0)
		return ("$");
	if (ft_strncmp(getter, "?", 1) == 0)
		return (ft_itoa(core->err_code));
	while (core->envp[++i])
	{
		if (ft_strncmp(getter, core->envp[i], ft_strlen(getter)) == 0)
		{
			values = ft_strchr(core->envp[i], '=');
			values = ft_strchr(values, values[1]);
		}
	}
	return (values);
}

void	add_envp(char *getter, char *values, t_core *core)
{
	size_t	i;
	char	**cpy;
	(void) values;
	i = -1;
	while (core->envp[++i])
		;
	cpy = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (core->envp[i])
	{
		cpy[i] = ft_strdup(core->envp[i]);
		i++;
	}
	cpy[i] = ft_strdup(getter);
	cpy[i] = ft_strjoin(cpy[i], values);
	cpy[i + 1] = 0;
	core->envp = cpy;
}
