/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/08 11:33:56 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//if not tokens
		pipe(pipe_fd);
		c_pid = fork();
		if (c_pid == 0)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			//if not builtins make execve
			execve((char *) core->execution_three->sons[i]->content, new_argv, core->envp);
			perror("execve");
			exit(1);
		}
		else
		{
			close(pipe_fd[1]);
			while (read(pipe_fd[0], &buf, 1) > 0)
				write(STDOUT_FILENO, &buf, 1);
			close(pipe_fd[0]);
		}
	}
}
