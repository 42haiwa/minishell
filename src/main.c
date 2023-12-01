/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 13:46:00 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_core	init(t_core *core, char **envp)
{
	parse_envp(core, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buf;
	t_core	core;

	buf = NULL;
	(void) argv;
	(void) argc;
	core = init(&core, envp);
	while (1)
	{
		buf = readline(PROMPT);
		//check_builtins(buf);
	}
}
