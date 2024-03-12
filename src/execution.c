/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/12 20:48:43 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_exec(t_core *core, t_exec *stru)
{
	stru->j = 1;
	if (ft_strcmp(core->execution_three->sons[stru->i]->content, "") == '\0')
		return (1);
	stru->new_argv = ft_calloc(core->execution_three->sons[stru->i]->sons_ctr
			+ 2, sizeof(char *));
	while (stru->j <= core->execution_three->sons[stru->i]->sons_ctr)
	{
		stru->new_argv[stru->j] = ft_strdup(
				core->execution_three->sons[stru->i]->sons[stru->j - 1]
				->content);
		stru->j++;
	}
	stru->new_argv[0] = ft_strdup(core->execution_three
			->sons[stru->i]->content);
	if (is_token(core->execution_three->sons[stru->i]->content))
	{
		if (ft_strncmp(core->execution_three->sons[stru->i]->content,
				"PIPE", 4) == 0)
			stru->pipe_ctr++;
		free_str_tab(stru->new_argv);
		return (1);
	}
	return (0);
}

int	second_exec(t_core *core, t_exec *s)
{
	if (check_builtins_no_fork(core->execution_three->sons[s->i]->content,
			s->new_argv, core->execution_three->sons[s->i]->sons_ctr + 1,
			core))
		return (1);
	s->check = ft_get_path(core, core->execution_three->sons[s->i]->content);
	if (!check_builtins_no_exec(core->execution_three->sons[s->i]->content)
		&& s->check)
	{
		s->test = core->execution_three->sons[s->i]->content;
		core->execution_three->sons[s->i]->content = ft_get_path(core, s->test);
		free(s->test);
	}
	if (s->check == NULL)
	{
		ft_putstr_fd(core->execution_three->sons[s->i]->content, 2);
		ft_putendl_fd(": command not found", 2);
		free_str_tab(s->new_argv);
		return (1);
	}
	free(s->check);
	return (0);
}

void	three_exec(t_core *core, t_exec *stru)
{
	if ((stru->i + 1) < (size_t) core->execution_three->sons_ctr
		&& core->execution_three->sons[stru->i]->outpipe)
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
	size_t	k;

	k = 0;
	while (stru->i - k > 1)
	{
		if (*((char *)core->execution_three->sons[stru->i - k - 2]->content) == '\0')
			k++;
		else
			break ;
	}
	if (stru->i - k > 1 && core->execution_three->sons[stru->i - k - 2]->outpipe)
	{
		printf("DEBUG test %zu\n", k);
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

void	pre_execution(t_core *core)
{
	size_t	i;
	size_t	k;

	i = -1;
	while (++i < (size_t) core->execution_three->sons_ctr)
	{
		if (i < (size_t) core->execution_three->sons_ctr - 1)
		{
			if (*((char *) core->execution_three->sons[i]->content) == '\0')
				continue ;
			k = 1;
			if (ft_strcmp(core->execution_three->sons[i + 1]->content, "PIPE") == 0)
			{
				printf("[%s] has pipe \n", (char *) core->execution_three->sons[i]->content);
				core->execution_three->sons[i]->outpipe = 1;
			}
			while (((size_t) i + k + 2 < (size_t) core->execution_three->sons_ctr) && *((char *)core->execution_three->sons[i + k]->content) == '\0')
			{
				if (((size_t) i + k + 2 < (size_t) core->execution_three->sons_ctr) && ft_strcmp(core->execution_three->sons[i + k + 2]->content, "PIPE") == 0)
				{
					printf("[%s] has pipe \n", (char *) core->execution_three->sons[i]->content);
					core->execution_three->sons[i]->outpipe = 1;
					break ;
				}
				k++;
			}
		}
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
		if (stru.c_pid != 0)
			dprintf(2, "pid = %d\n", stru.c_pid);
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
		free_str_tab(stru.new_argv);
	}
	end_exec(core, &stru);
}
