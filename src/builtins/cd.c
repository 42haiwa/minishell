/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:44:38 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/10 20:34:47 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv, int argc, t_core *core)
{
	int		check;

	(void) argc;
	(void) core;
	check = chdir(argv[1]);
	if (check != 0)
	{
		perror("cd");
		return ;
	}
}
