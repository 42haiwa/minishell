/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:44:38 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/13 14:19:56 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv, int argc, t_core *core)
{
	int		check;

	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		core->err_code = 1;
		return ;
	}
	if (argc <= 1)
	{
		check = chdir(get_envp("HOME", core));
		set_envp("PWD", getcwd(NULL, 0), core);
		core->err_code = 0;
		return ;
	}
	check = chdir(argv[1]);
	if (check != 0)
	{
		perror("cd");
		core->err_code = 1;
		return ;
	}
	core->err_code = 0;
	set_envp("PWD", getcwd(NULL, 0), core);
}
