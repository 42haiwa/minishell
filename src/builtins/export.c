/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:54:52 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/17 21:33:33 by aallou-v         ###   ########.fr       */
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
	res = ft_calloc(len + 2, sizeof(char));
	if (!res)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != '=')
	{
		res[len] = s[len];
		len++;
	}
	res[len] = '=';
	res[len + 1] = '\0';
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

void	export(char **argv, int argc, t_core *core)
{
	int	i;

	i = 1;
	if (argc <= 1)
		return ;
	while (i < argc)
	{
		if (ft_strchr(argv[i], '=') == NULL)
			return ;
		if (ft_strlen(get_envp(get_getter(argv[i]), core)) == 0)
			add_envp(get_getter(argv[i]), get_value(argv[i]), core);
		else
			set_envp(ft_strrchr(get_getter(argv[i]), '='),
				get_value(argv[i]), core);
		i++;
	}
}
