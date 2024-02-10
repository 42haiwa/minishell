/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:38:41 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/10 22:00:50 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_arg(char *buf, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
		free(argv[i++]);
	free(argv);
	free(buf);
	return (1);
}

int	check_builtins(char *buf, char **argv, int argc, t_core *core)
{
	if (ft_strncmp("pwd", buf, 3) == 0)
		pwd();
	if (ft_strncmp("env", buf, 3) == 0)
		env(core);
	if (ft_strncmp("echo", buf, 4) == 0)
		echo(argv, argc, core);
	if (ft_strncmp("env", buf, 3) == 0
		|| ft_strncmp("pwd", buf, 3) == 0
		|| ft_strncmp("echo", buf, 4) == 0)
		return (free_arg(buf, argv, argc));
	return (0);
}

int	check_builtins_no_fork(char *buf, char **argv, int argc, t_core *core)
{
	if (ft_strncmp("export", buf, 6) == 0)
		export(argv, argc, core);
	if (ft_strncmp("unset", buf, 5) == 0)
		unset(argv, argc, core);
	if (ft_strncmp("exit", buf, 4) == 0)
		ft_exit(argc, argv, core);
	if (ft_strncmp("cd", buf, 2) == 0)
		cd(argv, argc, core);
	if (ft_strncmp("cd", buf, 2) == 0
		|| ft_strncmp("exit", buf, 4) == 0
		|| ft_strncmp("export", buf, 6) == 0
		|| ft_strncmp("unset", buf, 5) == 0)
	{
		free(argv[0]);
		free(argv);
		return (1);
	}
	return (0);
}
