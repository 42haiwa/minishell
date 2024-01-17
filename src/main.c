/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/17 16:18:16 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_core *core, char **envp)
{
	core->envp = envp;
	core->execution_three = 0;
	core->son_pid = -1;
	core->lexer_out = "";
	core->folder = "";
}

int	main(int argc, char *argv[], char *envp[])
{
	char				*buf;
	t_core				*core;

	buf = NULL;
	(void) argc;
	(void) argv;
	core = ft_calloc(1, sizeof(t_core));
	if (!core)
		return (1);
	init(core, envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		buf = readline("\e[35mminishell \e[33m ➤ \e[21m\e[0m ");
		if (buf == NULL)
			break ;
		add_history(buf);
		pre_lexing(buf, core);
		free(buf);
		fill_three(core);
		parse_io(core);
		rm_sep_three(core->execution_three);
		execution(core);
		free(core->lexer_out);
	}
	printf("exit\n");
	ft_exit(1, NULL, core);
}
