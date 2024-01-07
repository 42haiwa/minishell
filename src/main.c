/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/04 18:31:13 by cjouenne         ###   ########.fr       */
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
	char				*buf;
	t_core				*core;
	struct sigaction	sa;

	buf = NULL;
	(void) argv;
	(void) argc;
	core = malloc(sizeof(t_core));
	if (!core)
		return (1);
	sa.sa_handler = handler;
	init(core, envp);
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		buf = readline(get_prompt(core));
		add_history(buf);
		if (buf[0] == 0)
			continue ;
		if (check_builtins(buf, core))
			continue ;
		pre_lexing(buf, core);
		if (PRINT_LEXER)
			printf("%s\n", core->lexer_out);
		fill_three(core);
		rm_sep_three(core->execution_three);
		execution(core);
	}
}
