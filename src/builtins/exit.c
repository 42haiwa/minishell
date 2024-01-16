/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:18:24 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/16 17:02:09 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int argc, char **argv, t_core *core)
{
	if (argc != 1 && argc != 2)
		ft_putstr_fd("error: to many arguments !\n", 2);
	free_three(core);
	if (argc == 2)
		exit(ft_atoi(argv[1]));
	else if (argc == 1)
		exit(0);
}
