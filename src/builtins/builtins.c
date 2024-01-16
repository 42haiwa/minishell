/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:38:41 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/16 17:02:36 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char *buf, char **argv, int argc, t_core *core)
{
	if (ft_strncmp("pwd", buf, ft_strlen(buf)) == 0)
		pwd();
	if (ft_strncmp("env", buf, ft_strlen(buf)) == 0)
		env(core);
	if (ft_strncmp("echo", buf, ft_strlen(buf)) == 0)
		echo(argv, argc, core);
	if (ft_strncmp("env", buf, ft_strlen(buf)) == 0 || ft_strncmp("pwd", buf, ft_strlen(buf)) == 0
		 || ft_strncmp("echo", buf, ft_strlen(buf)) == 0)
		return (1);
	return (0);
}

int	check_builtins_no_fork(char *buf, char **argv, int argc, t_core *core)
{
	if (ft_strncmp("export", buf, ft_strlen(buf)) == 0)
		export(argv, argc, core);
	if (ft_strncmp("unset", buf, ft_strlen(buf)) == 0)
		unset(argv, argc, core);
	if (ft_strncmp("exit", buf, ft_strlen(buf)) == 0)
		ft_exit(argc, argv, core);
	if (ft_strncmp("cd", buf, ft_strlen(buf)) == 0)
		cd(argv, argc, core);
	if (ft_strncmp("cd", buf, ft_strlen(buf)) == 0 || ft_strncmp("exit", buf, ft_strlen(buf)) == 0
		|| ft_strncmp("export", buf, ft_strlen(buf)) == 0 || ft_strncmp("unset", buf, ft_strlen(buf)) == 0)
		return (1);
	return (0);
}
