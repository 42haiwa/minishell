/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:38:41 by aallou-v          #+#    #+#             */
/*   Updated: 2023/12/10 20:37:13 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char *buf, char **argv, int argc, t_core *core)
{
	if (ft_strncmp("cd", buf, 2) == 0)
		cd(argv, argc, core);
	if (ft_strncmp("pwd", buf, 3) == 0)
		pwd();
	if (ft_strncmp("env", buf, 3) == 0)
		env(core);
	if (ft_strncmp("echo", buf, 4) == 0)
		echo(argv, argc, core);
	if (ft_strncmp("env", buf, 3) == 0 || ft_strncmp("pwd", buf, 3) == 0
		 || ft_strncmp("cd", buf, 3) == 0 || ft_strncmp("echo", buf, 4) == 0)
		return (1);
	return (0);
}

int	check_builtins_no_fork(char *buf, char **argv, int argc, t_core *core)
{
	(void) argv;
	(void) argc;
	(void) core;
	// EXPORT
	// UNSET
	if (ft_strncmp("exit", buf, 4) == 0)
		ft_exit();
	return (0);
}
