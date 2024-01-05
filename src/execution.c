/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/05 12:35:09 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

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
	int		**pipe_fd;
	size_t	i;
	ssize_t	j;
	pid_t	c_pid;
	size_t	pipe_ctr;

	pipe_ctr = 0;
	pipe_fd = ft_calloc(512, sizeof(int *));
	i = 0;
	while (i < 128)
	{
		pipe_fd[i] = ft_calloc(2, sizeof(int));
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
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
		if (is_token(core->execution_three->sons[i]->content))
		{	
			if (ft_strncmp(core->execution_three->sons[i]->content, "PIPE", 4) == 0)
				pipe_ctr++;
			continue ;
		}
		if (check_builtins(core->execution_three->sons[i]->content, core))
			continue ;
		core->execution_three->sons[i]->content = ft_strdup(ft_get_path(core, core->execution_three->sons[i]->content));

		errno = 0;
		if ((c_pid = fork()) == -1)
		{
			exit(1);
		}
		perror("fork");
		if (c_pid == 0)
		{
			if ((i + 1) < (size_t) core->execution_three->sons_ctr && ft_strncmp(core->execution_three->sons[i + 1]->content, "PIPE", 4) == 0)
			{
				errno = 0;
				dup2(pipe_fd[pipe_ctr][1], STDOUT_FILENO);
				perror("dup2");
				close(pipe_fd[pipe_ctr][1]);
				pipe_fd[pipe_ctr][1] = -1;
			}
			if (i > 1 && ft_strncmp(core->execution_three->sons[i - 1]->content, "PIPE", 4) == 0)
			{
				errno = 0;
				dup2(pipe_fd[pipe_ctr - 1][0], STDIN_FILENO);
				perror(ft_itoa(pipe_ctr - 1));
				close(pipe_fd[pipe_ctr - 1][0]);
				pipe_fd[pipe_ctr - 1][0] = -1;
			}
			execve(core->execution_three->sons[i]->content, new_argv, core->envp);
			perror("minishell");
			exit(1);
		}
		else
		{
			wait(NULL);
			if ((i + 1) < (size_t) core->execution_three->sons_ctr && ft_strncmp(core->execution_three->sons[i + 1]->content, "PIPE", 4) == 0)
			{
				close(pipe_fd[pipe_ctr][1]);
				pipe_fd[pipe_ctr][1] = -1;
			}
			if (i > 1 && ft_strncmp(core->execution_three->sons[i - 1]->content, "PIPE", 4) == 0)
			{
				close(pipe_fd[pipe_ctr - 1][0]);
				pipe_fd[pipe_ctr - 1][0] = -1;
			}
		}	
	}
	i = 0;
	while (i < 128)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}

void	_execution(t_core *core)
{
	int		pipe_fd[2];
	pid_t	c_pid;
	ssize_t	j;
	size_t	i;

	i = -1;
	if (pipe(pipe_fd) == -1) 
	{
		perror("pipe");
		exit(1);
	}
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
		if (is_token(core->execution_three->sons[i]->content))
			continue ;
		if (check_builtins(core->execution_three->sons[i]->content, core))
			continue ;
		core->execution_three->sons[i]->content = ft_strdup(ft_get_path(core, core->execution_three->sons[i]->content));
		c_pid = fork();
		perror("fork");
		if (c_pid == 0)
		{
			if (i > 1 && ft_strncmp(core->execution_three->sons[i - 1]->content, "PIPE", 4) == 0)
			{
				if (pipe_fd[0] != -1)
				{
					dup2(pipe_fd[0], STDIN_FILENO);
					close(pipe_fd[0]);
					perror("dup2");
					pipe_fd[0] = -1;
				}
			}
			if ((i + 1) < (size_t) core->execution_three->sons_ctr && ft_strncmp(core->execution_three->sons[i + 1]->content, "PIPE", 4) == 0)
			{
				if (pipe_fd[1] != -1)
				{
					dup2(pipe_fd[1], STDOUT_FILENO);
					printf("After dup2: stdin=%d, stdout=%d\n", STDIN_FILENO, STDOUT_FILENO);
					close(pipe_fd[1]);
					perror("dup2");
					pipe_fd[1] = -1;
				}
			}
			execve((char *) core->execution_three->sons[i]->content, new_argv, core->envp);
			perror("execve");
			exit(1);
		}
		else
		{
			wait(NULL);
			if (i > 1 && ft_strncmp(core->execution_three->sons[i - 1]->content, "PIPE", 4) == 0)
			{
				if (pipe_fd[1] != -1)
				{
					close(pipe_fd[1]);
					pipe_fd[1] = -1;
				}
			}
			if ((i + 1) < (size_t) core->execution_three->sons_ctr && ft_strncmp(core->execution_three->sons[i + 1]->content, "PIPE", 4) == 0)
			{
				if (pipe_fd[0] != -1)
				{
					close(pipe_fd[0]);
					pipe_fd[0] = -1;
				}
				if (pipe_fd[0] == -1 && pipe_fd[1] == -1)
				{
					if (pipe(pipe_fd) == -1) 
					{
						perror("pipe");
						exit(1);
					}
				}
			}
		}
	}
}
