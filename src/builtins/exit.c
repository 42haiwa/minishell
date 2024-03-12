/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:18:24 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/12 11:23:31 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_exit(int option, char **argv, t_core *core)
{
	if (core)
	{
		free_three(&core->execution_three);
		free_str_tab(core->envp);
	}
	free_str_tab(argv);
	exit(option);
}

/*
exit too many argument
   - exit world 42 = 2
   - exit 42 world = 1
exit world = 2
exit = 0
exit too many argument = 1
*/

void	ft_exit(int argc, char **argv, t_core *core)
{
	if (argc != 1 && argc != 2)
	{
		ft_putstr_fd("error: too many arguments\n", 2);
		core->err_code = 1;
	}
	else if (argc == 2)
		free_exit(ft_atoi(argv[1]), argv, core);
	else
		free_exit(1, argv, core);
}
