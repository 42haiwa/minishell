/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:41:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/12 19:53:35 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_part(t_parse *stru, t_core *core, char *path)
{
	if ((stru->j + 1 < core->execution_three->sons_ctr)
		&& ft_strncmp(core->execution_three->sons[stru->j]->content,
			"GREATGREAT", 10) == 0)
	{
		path = ft_substr(core->execution_three->sons[stru->j + 1]->content, 1,
				ft_strlen(core->execution_three->sons[stru->j + 1]->content)
				- 2);
		free(core->execution_three->sons[stru->j]->content);
		free(core->execution_three->sons[stru->j + 1]->content);
		core->execution_three->sons[stru->j]->content = ft_strdup("\0");
		core->execution_three->sons[stru->j + 1]->content = ft_strdup("\0");
		core->execution_three->sons[stru->i]->output_mode = 2;
		core->execution_three->sons[stru->i]->output = path;
		stru->fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		printf("%d\n", stru->fd);
		close(stru->fd);
	}
}

void	second_part_parse(t_parse *s, t_core *core, char *pth)
{
	if ((s->j + 1 < core->execution_three->sons_ctr)
		&& ft_strncmp(core->execution_three->sons[s->j]->content,
			"LESSLESS", 8) == 0)
	{
		pth = ft_substr(core->execution_three->sons[s->j + 1]->content, 1,
				ft_strlen(core->execution_three->sons[s->j + 1]->content) - 2);
		core->execution_three->sons[s->i]->heredoc_id = 1;
		s->fd = open("HEREDOC", O_WRONLY | O_CREAT | O_APPEND, 0644);
		s->buf = NULL;
		while (1)
		{
			s->tmp = readline("heredoc> ");
			s->buf = ft_strjoin(s->tmp, "\n");
			free(s->tmp);
			if (s->buf == NULL || ft_strcmp(s->buf, pth) == 0)
			{
				free(s->buf);
				break ;
			}
			ft_putstr_fd(s->buf, s->fd);
			free(s->buf);
		}
		close(s->fd);
		free(pth);
	}
}

void	part_three(t_parse *stru, t_core *core, char *path)
{
	if ((stru->j + 1 < core->execution_three->sons_ctr)
		&& ft_strncmp(core->execution_three->sons[stru->j]->content,
			"GREAT", 5) == 0)
	{
		path = ft_substr(core->execution_three->sons[stru->j + 1]->content, 1,
				ft_strlen(core->execution_three->sons[stru->j + 1]->content)
				- 2);
		free(core->execution_three->sons[stru->j]->content);
		free(core->execution_three->sons[stru->j + 1]->content);
		core->execution_three->sons[stru->j]->content = ft_strdup("\0");
		core->execution_three->sons[stru->j + 1]->content = ft_strdup("\0");
		core->execution_three->sons[stru->i]->output_mode = 1;
		core->execution_three->sons[stru->i]->output = path;
		stru->fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(stru->fd);
	}
}

void	part_four(t_parse *stru, t_core *core, char *path)
{
	if ((stru->j + 1 < core->execution_three->sons_ctr)
		&& ft_strncmp(core->execution_three->sons[stru->j]->content,
			"LESS", 4) == 0)
	{
		path = ft_substr(core->execution_three->sons[stru->j + 1]->content, 1,
				ft_strlen(core->execution_three->sons[stru->j + 1]->content)
				- 2);
		free(core->execution_three->sons[stru->j]->content);
		free(core->execution_three->sons[stru->j + 1]->content);
		core->execution_three->sons[stru->j]->content = ft_strdup("\0");
		core->execution_three->sons[stru->j + 1]->content = ft_strdup("\0");
		core->execution_three->sons[stru->i]->input = path;
	}
}

void	parse_io(t_core *core)
{
	char	*path;
	t_parse	stru;

	stru.i = 0;
	while (stru.i < core->execution_three->sons_ctr)
	{
		stru.j = stru.i;
		while (1)
		{
			if (stru.j >= core->execution_three->sons_ctr)
				break ;
			if (ft_strncmp(core->execution_three->sons[stru.j]->content,
					"PIPE", 4) == 0)
				break ;
			path = NULL;
			first_part(&stru, core, path);
			second_part_parse(&stru, core, path);
			free(path);
			part_three(&stru, core, path);
			part_four(&stru, core, path);
			stru.j++;
		}
		stru.i++;
	}
}
