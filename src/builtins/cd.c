/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:44:38 by cjouenne          #+#    #+#             */
/*   Updated: 2024/02/10 04:06:43 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv, int argc, t_core *core)
{
	int		check;

	(void) argc;
	(void) core;
	if (argc != 2)
	{
		ft_putstr_fd("cd: usage error !\n", 2);
		return ;
	}
	check = chdir(argv[1]);
	if (check != 0)
	{
		perror("cd");
		return ;
	}
}
