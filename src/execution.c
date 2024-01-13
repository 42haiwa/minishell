/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/13 04:29:32 by cjouenne         ###   ########.fr       */
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
	if (ft_strncmp(s, "GREAT", 5) == 0 && ft_strlen(s) <= 5)
		return (1);
	if (ft_strncmp(s, "LESS", 4) == 0 && ft_strlen(s) <= 4)
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
	int		o_fd;
	int		i_fd;
	size_t	cmd;

	cmd = 0;
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
		if (ft_strncmp(core->execution_three->sons[i]->content, "\0", 1) == 0)
			continue ;
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
		if (check_builtins_no_fork(core->execution_three->sons[i]->content, new_argv, core->execution_three->sons[i]->sons_ctr + 1, core))
			continue ;
		if (ft_get_path(core, core->execution_three->sons[i]->content))
			core->execution_three->sons[i]->content = ft_strdup(ft_get_path(core, core->execution_three->sons[i]->content));
		if ((c_pid = fork()) == -1)
			exit(1);
		core->son_pid = c_pid;
		if (c_pid == 0)
		{
			if ((i + 1) < (size_t) core->execution_three->sons_ctr && ft_strncmp(core->execution_three->sons[i + 1]->content, "PIPE", 4) == 0)
			{
				dup2(pipe_fd[pipe_ctr][1], STDOUT_FILENO);
				close(pipe_fd[pipe_ctr][1]);
				pipe_fd[pipe_ctr][1] = -1;
			}
			if ((core->execution_three->sons[i]->output) != 0)
			{
				if (core->execution_three->sons[i]->output_mode == 1)
					o_fd = open(core->execution_three->sons[i]->output,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (core->execution_three->sons[i]->output_mode == 2)
					o_fd = open(core->execution_three->sons[i]->output,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
				dup2(o_fd, STDOUT_FILENO);
				close(o_fd);
			}
			if (i > 1 && ft_strncmp(core->execution_three->sons[i - 1]->content, "PIPE", 4) == 0)
			{
				dup2(pipe_fd[pipe_ctr - 1][0], STDIN_FILENO);
				close(pipe_fd[pipe_ctr - 1][0]);
				pipe_fd[pipe_ctr - 1][0] = -1;
			}
			if ((core->execution_three->sons[i]->input) != 0)
			{
				i_fd = open(core->execution_three->sons[i]->input, 
					O_RDONLY);
				dup2(i_fd, STDIN_FILENO);
				close(i_fd);
			}
			if (core->execution_three->sons[i]->heredoc_id)
			{
				i_fd = open("HEREDOC", 
					O_RDONLY);
				dup2(i_fd, STDIN_FILENO);
				close(i_fd);
			}
			if (check_builtins(core->execution_three->sons[i]->content, new_argv, core->execution_three->sons[i]->sons_ctr + 1, core))
				exit(0);
			execve(core->execution_three->sons[i]->content, new_argv, core->envp);
			perror("minishell");
			exit(1);
		}
		else
		{
			cmd++;
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
	while (i < cmd)
	{
			int status;
			wait(&status);
			core->err_code = WEXITSTATUS(status);
			i++;
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
