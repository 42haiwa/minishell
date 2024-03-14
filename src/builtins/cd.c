/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:44:38 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/14 14:18:39 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_old_pwd(t_core *core)
{
	if (ft_strcmp(get_envp("OLDPWD", core), "") == 0)
		add_envp("OLDPWD", getcwd(NULL, 0), core);
	else	
		set_envp("OLDPWD", getcwd(NULL, 0), core);
}

static void	update_pwd(t_core *core)
{
	if (ft_strcmp(get_envp("PWD", core), "") == 0)
		add_envp("PWD", getcwd(NULL, 0), core);
	else	
		set_envp("PWD", getcwd(NULL, 0), core);
}

static int	cd2(int argc, t_core *core)
{
	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		core->err_code = 1;
		return (0);
	}
	return (1);
}

void	cd(char **argv, int argc, t_core *core)
{
	int		check;

	if (!cd2(argc, core))
		return ;
	if (argc <= 1)
	{
		update_old_pwd(core);
		check = chdir(get_envp("HOME", core));
		update_pwd(core);
		core->err_code = 0;
		return ;
	}
	update_old_pwd(core);
	check = chdir(argv[1]);
	if (check != 0)
	{
		perror("cd");
		core->err_code = 1;
		return ;
	}
	core->err_code = 0;
	update_pwd(core);
}
