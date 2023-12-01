/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 13:51:40 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_core *core, char **envp)
{
	core->env = malloc(sizeof(t_env));
	parse_envp(core, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buf;
	t_core	*core;

	buf = NULL;
	(void) argv;
	(void) argc;
	core = malloc(sizeof(t_core));
	init(core, envp);
	while (1)
	{
		buf = readline(PROMPT);
		//check_builtins(buf);
	}
}
