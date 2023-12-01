/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 12:24:10 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_core	init(t_core *core, char **envp)
{
	core->env = parse_envp();
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buf;
	t_core	core;

	buf = NULL;
	core = init(&core, envp);
	while (1)
	{
		buf = readline(PROMPT);
		//heck_builtins(buf);
	}
}
