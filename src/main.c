/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/14 20:04:18 by cjouenne         ###   ########.fr       */
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
	core->son_pid = -1;
}

t_core	*g_core;

int	main(int argc, char *argv[], char *envp[])
{
	char				*buf;
	t_core				*core;

	buf = NULL;
	(void) argv;
	(void) argc;
	core = malloc(sizeof(t_core));
	if (!core)
		return (1);
	init(core, envp);
	g_core = core;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		buf = readline("\e[35mminishell \e[33m ➤ \e[21m\e[0m ");
		if (buf == NULL)
			break ;
		add_history(buf);
		if (buf[0] == 0)
			continue ;
		pre_lexing(buf, core);
		if (PRINT_LEXER)
			printf("%s\n", core->lexer_out);
		fill_three(core);
		parse_io(core);
		rm_sep_three(core->execution_three);
		execution(core);
	}
	printf("exit\n");
	exit(0);
}
