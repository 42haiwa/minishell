/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:44:38 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/13 18:34:46 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv, int argc, t_core *core)
{
	int		check;

	(void) argc;
	(void) core;
	printf("my cd\n");
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
