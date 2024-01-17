/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:32:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/17 21:32:40 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **argv, int argc, t_core *core)
{
	int	i;
	int	is_n;

	(void) core;
	i = 1;
	is_n = 0;
	if (!(argc > 1))
		return ;
	if (argv[1][0] == '-' && argv[1][1] == 'n')
	{
		is_n = 1;
		i++;
	}
	while (i < argc)
	{
		if (i == (argc - 1))
			printf("%s", argv[i]);
		else
			printf("%s ", argv[i]);
		i++;
	}
	if (!is_n)
		printf("\n");
}
