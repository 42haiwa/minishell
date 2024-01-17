/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:13:24 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/17 21:33:06 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_core *core)
{
	int	i;

	i = -1;
	while (core->envp[++i])
		ft_putendl_fd(core->envp[i], 1);
}
