/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:38:41 by aallou-v          #+#    #+#             */
/*   Updated: 2023/12/02 00:07:53 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_builtins(char *buf, t_core *core)
{
	if (ft_strncmp("exit", buf, 4) == 0)
		ft_exit();
	if (ft_strncmp("cd", buf, 2) == 0)
		cd(buf, core);
}