/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:44:38 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/08 11:33:19 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(const char *path, t_core *core)
{
	char	*tmp;
	int		check;

	tmp = ft_strdup(ft_strchr(path, '/'));
	check = chdir(tmp);
	if (!check)
	{
		ft_printf("cd: no such file or directory\nError: %i\n", check);
		return ;
	}
	set_envp("PWD", tmp, core);
}
