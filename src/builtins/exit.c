/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:18:24 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/17 16:06:23 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all(t_core *core)
{
	int	i;

	i = -1;
	//free(core->envp);
	if (core->lexer_out)
		free(core->lexer_out);
}

static void	free_exit(int option, t_core *core)
{
	free_all(core);
	exit(option);
}

void	ft_exit(int argc, char **argv, t_core *core)
{
	if (argc != 1 && argc != 2)
		ft_putstr_fd("error: to many arguments !\n", 2);
	free_three(core);
	if (argc == 2)
		free_exit(ft_atoi(argv[1]), core);
	else if (argc == 1)
		free_exit(0, core);
}
