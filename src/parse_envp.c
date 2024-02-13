/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:39:48 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/13 22:23:53 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_getter(char const *s)
{
	size_t	len;
	char	*res;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != '=')
	{
		res[len] = s[len];
		len++;
	}
	res[len] = '\0';
	return (res);
}

void	set_envp(char *getter, char *new_values, t_core *core)
{
	int		i;
	char	*values;
	char	*tmp;
	char	*tmp2;

	i = -1;
	values = "";
	while (core->envp[++i])
	{
		tmp = get_getter(core->envp[i]);
		if (ft_strcmp(getter, tmp) == 0)
		{
			tmp2 = ft_strjoin(getter, "=");
			values = ft_strjoin(tmp2, new_values);
			free(core->envp[i]);
			core->envp[i] = NULL;
			core->envp[i] = ft_strdup(values);
			free(tmp2);
			free(values);
		}
		free(tmp);
	}
}

char	*get_envp(char *getter, t_core *core)
{
	int		i;
	char	*values;
	char	*tmp;

	i = -1;
	values = "";
	if (getter[0] == '\0')
		return ("$");
	if (ft_strcmp(getter, "?") == 0)
		return (ft_itoa(core->err_code));
	while (core->envp[++i])
	{
		tmp = get_getter(core->envp[i]);
		if (ft_strcmp(getter, tmp) == 0)
		{
			values = ft_strchr(core->envp[i], '=');
			values = ft_strchr(values, values[1]);
		}
		free(tmp);
	}
	return (values);
}

void	add_envp(char *getter, char *values, t_core *core)
{
	size_t	i;
	char	**cpy;

	i = 0;
	while (core->envp[i])
		i++;
	cpy = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (core->envp[i])
	{
		cpy[i] = core->envp[i];
		i++;
	}
	cpy[i] = ft_strjoin(getter, values);
	free(core->envp);
	core->envp = cpy;
}

void	remove_envp(char *getter, t_core *core)
{
	size_t	i;
	size_t	j;
	char	**cpy;
	char	*tmp;

	i = 0;
	while (core->envp[i])
		i++;
	cpy = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (core->envp[++i])
	{
		tmp = get_getter(core->envp[i]);
		if (ft_strcmp(getter, tmp) == 0)
			free(core->envp[i]);
		else
		{
			cpy[j] = core->envp[i];
			j++;
		}
		free(tmp);
	}
	free(core->envp);
	core->envp = cpy;
}
