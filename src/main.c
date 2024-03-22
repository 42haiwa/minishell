/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/22 18:13:11 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_tab(char **str_tab)
{
	size_t	i;

	if (str_tab)
	{
		i = 0;
		while (str_tab[i])
			free(str_tab[i++]);
		free(str_tab);
	}
}

void	init(t_core *core, char **envp)
{
	struct sigaction	new_action;
	size_t				i;

	i = 0;
	while (envp[i])
		i++;
	core->envp = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (envp[++i])
		core->envp[i] = ft_strdup(envp[i]);
	core->execution_three = 0;
	core->son_pid = -1;
	core->lexer_out = NULL;
	core->folder = "";
	core->err_code = 0;
	signal(SIGINT, handler);
	new_action.sa_handler = SIG_IGN;
	new_action.sa_flags = 0;
	sigemptyset(&new_action.sa_mask);
	sigaction(SIGQUIT, &new_action, NULL);
}

void	free_lexing(t_core *core)
{
	size_t	i;

	i = -1;
	if (core->get_d_quote != NULL)
	{
		while (core->get_d_quote[++i])
			free(core->get_d_quote[i]);
		free(core->get_d_quote);
	}
	i = -1;
	if (core->get_quote != NULL)
	{
		while (core->get_quote[++i])
			free(core->get_quote[i]);
		free(core->get_quote);
	}
}

int	start(char *buf, t_core *core)
{
	char	*error;
	
	add_history(buf);
	error = check_extra(buf);
	if (error)
	{
		ft_putendl_fd(error, 2);
		return (0);
	}
	pre_lexing(buf, core);
	if (core->print_lex > 1)
		printf("%s\n", core->lexer_out);
	free_lexing(core);
	core->execution_three = node_init(NULL);
	fill_three(core);
	if (core->print_lex > 1)
		rprint(core->execution_three);
	parse_io(core);
	rm_sep_three(core->execution_three);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buf;
	t_core	core;

	buf = NULL;
	core.print_lex = argc;
	(void) argv;
	init(&core, envp);
	while (1)
	{
		buf = readline("\e[35mminishell \e[33m ➤ \e[21m\e[0m ");
		if (buf == NULL)
		{
			printf("exit\n");
			ft_exit(1, NULL, &core);
			break ;
		}
		if (start(buf, &core))
		{
			pre_execution(&core);
			execution(&core);
			free_three(&core.execution_three);
		}
	}
}
