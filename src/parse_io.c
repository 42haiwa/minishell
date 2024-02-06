/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:41:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/06 19:55:29 by aallou-v         ###   ########.fr       */
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
		close(stru->fd);
	}
}

void	second_part(t_parse *s, t_core *core, char *path)
{
	char	*buf;

	if ((s->j + 1 < core->execution_three->sons_ctr)
		&& ft_strncmp(core->execution_three->sons[s->j]->content,
			"LESSLESS", 8) == 0)
	{
		path = ft_substr(core->execution_three->sons[s->j + 1]->content, 1,
				ft_strlen(core->execution_three->sons[s->j + 1]->content) - 2);
		core->execution_three->sons[s->i]->heredoc_id = 1;
		s->fd = open("HEREDOC", O_WRONLY | O_CREAT | O_APPEND, 0644);
		buf = NULL;
		while (1)
		{
			buf = readline("heredoc> ");
			buf = ft_strjoin(buf, "\n");
			if (ft_strncmp(buf, path, ft_strlen(path)) == 0)
			{
				free(buf);
				break ;
			}
			ft_putstr_fd(buf, s->fd);
			free(buf);
		}
		close(s->fd);
	}
}

void	part_three(t_parse *stru, t_core *core, char *path)
{
	if ((stru->j + 1 < core->execution_three->sons_ctr)
		&& ft_strncmp(core->execution_three->sons[stru->j]->content,
			"GREAT", 5) == 0)
	{
		path = ft_substr(core->execution_three->sons[stru->j + 1]->content, 1, ft_strlen(core->execution_three->sons[stru->j + 1]->content) - 2);
		free(core->execution_three->sons[stru->j]->content);
		free(core->execution_three->sons[stru->j + 1]->content);
		core->execution_three->sons[stru->j]->content = ft_strdup("\0");
		core->execution_three->sons[stru->j + 1]->content = ft_strdup("\0");
		core->execution_three->sons[stru->i]->output_mode = 1;
		core->execution_three->sons[stru->i]->output = path;
		stru->fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(stru->fd);
	}
	if ((stru->j + 1 < core->execution_three->sons_ctr)
		&& ft_strncmp(core->execution_three->sons[stru->j]->content,
			"LESS", 4) == 0)
	{
		path = ft_substr(core->execution_three->sons[stru->j + 1]->content, 1, ft_strlen(core->execution_three->sons[stru->j + 1]->content) - 2);
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
			if (ft_strncmp(core->execution_three->sons[stru.j]->content, "PIPE", 3) == 0)
				break ;
			first_part(&stru, core, path);
			second_part(&stru, core, path);
			part_three(&stru, core, path);
			stru.j++;
		}
		stru.i++;
	}
}
