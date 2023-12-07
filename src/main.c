/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/07 15:35:04 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_core *core)
{
	int	i;

	i = -1;
	while (core->envp[++i])
		free(core->envp[i]);
	free(core->envp);
	free(core->folder);
	free(core->lexer_out);
	free(core->prompt);
}

void	init(t_core *core, char **envp)
{
	core->envp = envp;
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
		buf = readline(get_prompt(core));
		if (buf[0] == 0)
			continue ;
		pre_lexing(buf, core);
		printf("------------------\n");
		fill_three(core);
		printf("------------------\n");
		node_print_recurse(core->execution_three);
		check_builtins(buf, core);
	}
}
