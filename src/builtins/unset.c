/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:39:40 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/12 15:21:30 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **argv, int argc, t_core *core)
{
	int	i;

	i = 1;
	core->err_code = 0;
	if (argc <= 1)
		return ;
	while (i < argc)
	{
		remove_envp(argv[i], core);
		i++;
	}
}
