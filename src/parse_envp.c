/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:39:48 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/12 23:46:14 by aallou-v         ###   ########.fr       */
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
