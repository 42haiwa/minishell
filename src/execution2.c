/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:03:47 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/10 21:57:31 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	five_exec(t_core *core, t_exec *stru)
{
	char	*cmd;
	int		argc;
	
	cmd = ft_strdup(core->execution_three->sons[stru->i]->content);
	argc = core->execution_three->sons[stru->i]->sons_ctr + 1;
	free_three(core->execution_three);
	if (check_builtins(cmd, stru->new_argv, argc, core))
		exit(0);
	execve(cmd, stru->new_argv, core->envp);
	perror("minishell");
	exit(1);
}

void	six_exec(t_core *core, t_exec *stru)
{
	stru->cmd++;
	if ((stru->i + 1) < (size_t) core->execution_three->sons_ctr
		&& ft_strncmp(core->execution_three->sons[stru->i + 1]->content,
			"PIPE", 4) == 0)
	{
		ft_close(stru->pipe_fd[stru->pipe_ctr][1]);
		stru->pipe_fd[stru->pipe_ctr][1] = -1;
	}
	if (stru->i > 1 && ft_strncmp(core->execution_three->sons[stru->i - 1]
			->content, "PIPE", 4) == 0)
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
	int	status;

	stru->i = 0;
	while (stru->i < stru->cmd)
	{
		wait(&status);
		if (access("HEREDOC", F_OK) != -1)
			unlink("HEREDOC");
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
