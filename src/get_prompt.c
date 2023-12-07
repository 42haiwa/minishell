/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:56:18 by aallou-v          #+#    #+#             */
/*   Updated: 2023/12/08 00:23:16 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(t_core *core)
{
	char	*tmp;
	char	**split;
	int		i;
	
	core->prompt = ft_strdup("\e[36m");
	tmp = core->prompt;
	core->prompt = ft_strjoin(tmp, get_envp("USER", core));
	free(tmp);
	core->prompt = ft_strjoin(core->prompt, "@");
	tmp = ft_strdup(ft_substr(get_envp("SESSION_MANAGER", core), 6, 6));
	core->prompt = ft_strjoin(core->prompt, tmp);
	core->prompt = ft_strjoin(core->prompt, " \e[35m/");
	tmp = get_envp("PWD", core);
	split = ft_split(tmp, '/');
	i = 0;
	while (split[i])
		i++;
	core->prompt = ft_strjoin(core->prompt, split[i - 1]);
	core->prompt = ft_strjoin(core->prompt, "\e[33m ➤ \e[21m\e[0m ");
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return (core->prompt);
}
