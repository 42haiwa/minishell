/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:39:40 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/17 21:33:53 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **argv, int argc, t_core *core)
{
	int	i;

	i = 1;
	if (argc <= 1)
		return ;
	while (i < argc)
	{
		remove_envp(argv[i], core);
		i++;
	}
}
