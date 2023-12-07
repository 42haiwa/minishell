/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/07 16:44:15 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_core *core)
{
	int		pipe_fd[2];
	pid_t	c_pid;
	char	buf;

	// 0 IN
	// 1 OUT
	pipe(pipe_fd);
	c_pid = fork();
	if (c_pid == 0) // SON
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[0], 1);
		char	*new_argv[] = {""};
		execve((char *) core->execution_three->sons[0]->content, NULL, core->envp);
		close(pipe_fd[1]);
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		while (read(pipe_fd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);
		close(pipe_fd[0]);
	}
}
