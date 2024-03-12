/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:13:24 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/12 15:19:35 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_core *core)
{
	size_t	i;

	i = -1;
	while (core->envp[++i])
		ft_putendl_fd(core->envp[i], 1);
	core->err_code = 0;
}
