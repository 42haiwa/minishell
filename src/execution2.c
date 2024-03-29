/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:03:47 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/26 15:20:25 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	five_exec(t_core *core, t_exec *stru)
{
	char	*cmd;
	int		argc;

	cmd = ft_strdup(core->execution_three->sons[stru->i]->content);
	argc = core->execution_three->sons[stru->i]->sons_ctr + 1;
	free_three(&core->execution_three);
	if (check_builtins(cmd, stru->new_argv, argc, core))
		exit(0);
	execve(cmd, stru->new_argv, core->envp);
	perror("minishell");
	exit(1);
}

void	six_exec(t_core *core, t_exec *stru)
{
	size_t	k;

	k = 0;
	while (stru->i - k > 1)
	{
		if (*((char *)core->execution_three->sons[stru->i - k - 2]->content) == '\0')
			k++;
		else
			break ;
	}

	stru->cmd++;
	if ((stru->i + 1) < (size_t) core->execution_three->sons_ctr
		&& core->execution_three->sons[stru->i]->outpipe)
	{
		ft_close(stru->pipe_fd[stru->pipe_ctr][1]);
		stru->pipe_fd[stru->pipe_ctr][1] = -1;
	}
	if (stru->i - k > 1 && core->execution_three->sons[stru->i - k - 2]->outpipe)
	{
		ft_close(stru->pipe_fd[stru->pipe_ctr - 1][0]);
		stru->pipe_fd[stru->pipe_ctr - 1][0] = -1;
	}
}

void	init_exec(t_exec *stru)
{
	stru->cmd = 0;
	stru->pipe_ctr = 0;
	stru->i = 0;
	while (stru->i < 128)
	{
		if (pipe(stru->pipe_fd[stru->i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		stru->i++;
	}
	stru->i = -1;
}

void	end_exec(t_core *core, t_exec *stru)
{
	int		status;

	stru->i = 0;
	while (stru->i < stru->cmd)
	{
		wait(&status);
		core->err_code = WEXITSTATUS(status);
		stru->i++;
	}
	stru->i = 0;
	while (stru->i < 128)
	{
		ft_close(stru->pipe_fd[stru->i][0]);
		ft_close(stru->pipe_fd[stru->i][1]);
		stru->i++;
	}
}
