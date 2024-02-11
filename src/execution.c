/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2024/02/11 01:23:49 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_exec(t_core *core, t_exec *stru)
{
	if (ft_strncmp(core->execution_three->sons[stru->i]->content, "\0", 1) == 0)
		return (1);
	stru->new_argv = ft_calloc(core->execution_three->sons[stru->i]->sons_ctr
			+ 2, sizeof(char *));
	stru->j = 1;
	while (stru->j <= core->execution_three->sons[stru->i]->sons_ctr)
	{
		stru->new_argv[stru->j] = ft_strdup(
			core->execution_three->sons[stru->i]->sons[stru->j - 1]->content);
		stru->j++;
	}
	stru->new_argv[0] = ft_strdup(core->execution_three
			->sons[stru->i]->content);
	stru->new_argv[core->execution_three->sons[stru->i]->sons_ctr + 1] = NULL;
	if (is_token(core->execution_three->sons[stru->i]->content))
	{
		if (ft_strncmp(core->execution_three->sons[stru->i]->content,
				"PIPE", 4) == 0)
			stru->pipe_ctr++;
		free(stru->new_argv[0]);
		free(stru->new_argv);
		return (1);
	}
	return (0);
}

int	second_exec(t_core *core, t_exec *s)
{
	if (check_exit(core->execution_three->sons[s->i]->content))
	{
		free(s->new_argv[0]);
		ft_exit(0, NULL, NULL);
	}
	if (check_builtins_no_fork(core->execution_three->sons[s->i]->content,
			s->new_argv, core->execution_three->sons[s->i]->sons_ctr + 1,
			core))
	{
		// if (ft_strncmp("exit", core->execution_three->sons[s->i]
		// 		->content, 4) == 0)
		// 	free(s->new_argv[0]);
		return (1);
	}
	s->check = ft_get_path(core, core->execution_three->sons[s->i]->content);
	if (!check_builtins_no_exec(core->execution_three->sons[s->i]->content)
		&& s->check)
	{
		s->test = core->execution_three->sons[s->i]->content;
		core->execution_three->sons[s->i]->content = ft_get_path(core, s->test);
		free(s->test);
	}
	free(s->check);
	return (0);
}

void	three_exec(t_core *core, t_exec *stru)
{
	if ((stru->i + 1) < (size_t) core->execution_three->sons_ctr
		&& ft_strncmp(core->execution_three->sons[stru->i + 1]->content,
			"PIPE", 4) == 0)
	{
		dup2(stru->pipe_fd[stru->pipe_ctr][1], STDOUT_FILENO);
		ft_close(stru->pipe_fd[stru->pipe_ctr][1]);
		stru->pipe_fd[stru->pipe_ctr][1] = -1;
	}
	if ((core->execution_three->sons[stru->i]->output) != 0)
	{
		if (core->execution_three->sons[stru->i]->output_mode == 1)
			stru->o_fd = open(core->execution_three->sons[stru->i]->output,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (core->execution_three->sons[stru->i]->output_mode == 2)
			stru->o_fd = open(core->execution_three->sons[stru->i]->output,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(stru->o_fd, STDOUT_FILENO);
		ft_close(stru->o_fd);
	}
}

void	four_exec(t_core *core, t_exec *stru)
{
	if (stru->i > 1 && ft_strncmp(core->execution_three->sons[stru->i - 1]
			->content, "PIPE", 4) == 0)
	{
		dup2(stru->pipe_fd[stru->pipe_ctr - 1][0], STDIN_FILENO);
		ft_close(stru->pipe_fd[stru->pipe_ctr - 1][0]);
		stru->pipe_fd[stru->pipe_ctr - 1][0] = -1;
	}
	if ((core->execution_three->sons[stru->i]->input) != 0)
	{
		stru->i_fd = open(core->execution_three->sons[stru->i]->input,
				O_RDONLY);
		dup2(stru->i_fd, STDIN_FILENO);
		ft_close(stru->i_fd);
	}
	if (core->execution_three->sons[stru->i]->heredoc_id)
	{
		stru->i_fd = open("HEREDOC", O_RDONLY);
		dup2(stru->i_fd, STDIN_FILENO);
		ft_close(stru->i_fd);
	}
}

void	execution(t_core *core)
{
	t_exec	stru;
	
	init_exec(&stru);
	while (++stru.i < (size_t) core->execution_three->sons_ctr)
	{
		if (first_exec(core, &stru) == 1)
			continue ;
		if (second_exec(core, &stru) == 1)
			continue ;
		stru.c_pid = fork();
		if (stru.c_pid == -1)
			exit(1);
		core->son_pid = stru.c_pid;
		if (stru.c_pid == 0)
		{
			three_exec(core, &stru);
			four_exec(core, &stru);
			five_exec(core, &stru);
		}
		else
			six_exec(core, &stru);
		free(stru.new_argv[0]);
		free(stru.new_argv);
	}
	end_exec(core, &stru);
}
