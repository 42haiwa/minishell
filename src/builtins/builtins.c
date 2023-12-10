/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:38:41 by aallou-v          #+#    #+#             */
/*   Updated: 2023/12/08 11:14:38 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char *buf, t_core *core)
{
	if (ft_strncmp("exit", buf, 4) == 0)
	{
		ft_exit();
		return (1);
	}
	if (ft_strncmp("cd", buf, 2) == 0)
	{
		cd(buf, core);
		return (1);
	}
	return (0);
}
