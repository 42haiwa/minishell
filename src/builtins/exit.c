/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:18:24 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/13 10:56:58 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || ((str[i] == '+' || str[i] == '-') && !i)))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	free_exit(int option, char **argv, t_core *core)
{
	if (core)
	{
		free_three(&core->execution_three);
		free_str_tab(core->envp);
	}
	free_str_tab(argv);
	exit(option);
}

/*
exit too many argument
   - exit world 42 = 2
   - exit 42 world = 1
exit world = 2
exit = 0
exit too many argument = 1
*/

void	ft_exit(int argc, char **argv, t_core *core)
{
	if (argc == 1)
	{
		free_exit(0, argv, core);
	}
	else
	{
		if (is_valid(argv[1]))
		{
			if (argc > 2)
			{
				ft_putstr_fd("error: too many arguments\n", 2);
				core->err_code = 1;
				return ;
			}
			else
			{
				free_exit(ft_atoi(argv[1]), argv, core);
			}
		}
		else
		{
			free_exit(2, argv, core);
		}
	}
}
