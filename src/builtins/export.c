/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:54:52 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/13 23:38:28 by aallou-v         ###   ########.fr       */
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

static char	*get_value(char const *s)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	i++;
	len = 0;
	while (s[len])
		len++;
	j = 0;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[j] = s[i];
		i++;
		j++;
	}
	return (res);
}

static void	free_export(char *getter, char *values, char *tmp)
{
	free(getter);
	free(values);
	free(tmp);
}

static int	pre_export(int argc, t_core *core)
{
	if (argc <= 1)
	{
		env(core);
		return (1);
	}
	return (0);
}

void	export(char **argv, int argc, t_core *core)
{
	int		i;
	char	*getter;
	char	*values;
	char	*tmp;

	if (pre_export(argc, core))
		return ;
	i = 0;
	tmp = NULL;
	while (++i < argc)
	{
		if (ft_strchr(argv[i], '=') == NULL)
			return ;
		getter = get_getter(argv[i]);
		values = get_value(argv[i]);
		if (ft_strlen(get_envp(getter, core)) == 0)
		{
			tmp = ft_strjoin(getter, "=");
			add_envp(tmp, values, core);
		}
		else
			set_envp(getter, values, core);
		free_export(getter, values, tmp);
	}
}
