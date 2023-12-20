/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/20 16:43:52 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/types.h>
#include <sys/wait.h>

static int	is_token(char const *s)
{
	if (ft_strncmp(s, "PIPE", 4) == 0)
		return (1);
	if (ft_strncmp(s, "SEMICOLON", 9) == 0)
		return (1);
	if (ft_strncmp(s, "GREATGREAT", 10) == 0)
		return (1);
	if (ft_strncmp(s, "LESSLESS", 8) == 0)
		return (1);
	if (ft_strncmp(s, "GREAT", 5) == 0)
		return (1);
	if (ft_strncmp(s, "LESS", 4) == 0)
		return (1);
	return (0);
}

void	execution(t_core *core)
{
	int		pipe_fd[2];
	pid_t	c_pid;
	char	buf;
	ssize_t	j;
	size_t	i;

	i = -1;
	while (++i < (size_t) core->execution_three->sons_ctr)
	{
		char *new_argv[core->execution_three->sons[i]->sons_ctr + 2];
		j = 1;
		while (j <= core->execution_three->sons[i]->sons_ctr)
		{
			new_argv[j] = (char *) core->execution_three->sons[i]->sons[j - 1]->content;
			j++;
		}
		new_argv[0] = (char *) core->execution_three->sons[i]->content;
		new_argv[core->execution_three->sons[i]->sons_ctr + 1] = NULL;
		// 0 IN
		// 1 OUT
		if (is_token(core->execution_three->sons[i]->content))
			continue ;
		//check_builtins
		if (check_builtins(core->execution_three->sons[i]->content, core))
			continue ;
		core->execution_three->sons[i]->content = ft_strdup(ft_get_path(core, core->execution_three->sons[i]->content));
		if (i > 1 && ft_strncmp(core->execution_three->sons[i - 1]->content, "PIPE", 4) != 0)
		{
			pipe(pipe_fd);
			//perror("pipe");
		}
		if (i == 0)
		{
			pipe(pipe_fd);
			//perror("pipe");
		}
		c_pid = fork();
		//perror("fork");
		if (c_pid == 0)
		{
			if (i > 1 && ft_strncmp(core->execution_three->sons[i - 1]->content, "PIPE", 4) == 0)
			{
				dup2(pipe_fd[0], STDIN_FILENO);
				//perror("dup2");
				close(pipe_fd[0]);
			}
			if ((i + 1) < (size_t) core->execution_three->sons_ctr && ft_strncmp(core->execution_three->sons[i + 1]->content, "PIPE", 4) == 0)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				//perror("dup2");
				close(pipe_fd[1]);
			}
			if (!(i > 1 && ft_strncmp(core->execution_three->sons[i - 1]->content, "PIPE", 4) == 0)
						&& !((i + 1) < (size_t) core->execution_three->sons_ctr && ft_strncmp(core->execution_three->sons[i + 1]->content, "PIPE", 4) == 0))
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			//if not builtins make execve
			execve((char *) core->execution_three->sons[i]->content, new_argv, core->envp);
			//perror("execve");
			exit(1);
		}
		else
		{
			close(pipe_fd[1]);
			if ((i + 1) < (size_t) core->execution_three->sons_ctr && ft_strncmp(core->execution_three->sons[i + 1]->content, "PIPE", 4) == 0)
			{
					waitpid(c_pid, NULL, 0);
					continue ;
			}
			else
			{
				waitpid(c_pid, NULL, 0);
				while (read(pipe_fd[0], &buf, 1) > 0)
					write(STDOUT_FILENO, &buf, 1);
				close(pipe_fd[0]);
			}
		}
	}
}
