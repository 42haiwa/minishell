/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:54:52 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/13 21:02:10 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(char **argv, int argc, t_core *core)
{
	(void) argv;
	(void) argc;
	ft_putendl_fd("TEST\n", 1);
	add_envp("SALUT=", "test", core);
}