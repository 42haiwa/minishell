/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:41:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/17 21:41:20 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_io(t_core *core)
{
	int		i;
	int		j;
	char	*path;
	int		fd;

	i = 0;
	while (i < core->execution_three->sons_ctr)
	{
		j = i;
		while (1)
		{
			if (j >= core->execution_three->sons_ctr)
				break ;
			if (ft_strncmp(core->execution_three->sons[j]->content, "PIPE", 3) == 0)
				break ;
			if ((j + 1 < core->execution_three->sons_ctr) && ft_strncmp(core->execution_three->sons[j]->content, "GREATGREAT", 10) == 0)
			{
				path = ft_substr(core->execution_three->sons[j + 1]->content, 1, ft_strlen(core->execution_three->sons[j + 1]->content) - 2);
				core->execution_three->sons[j]->content = "\0";
				core->execution_three->sons[j + 1]->content = "\0";
				core->execution_three->sons[i]->output_mode = 2;
				core->execution_three->sons[i]->output = ft_strdup(path);
				fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
				close(fd);
			}
			if ((j + 1 < core->execution_three->sons_ctr) && ft_strncmp(core->execution_three->sons[j]->content, "LESSLESS", 8) == 0)
			{
				path = ft_substr(core->execution_three->sons[j + 1]->content, 1, ft_strlen(core->execution_three->sons[j + 1]->content) - 2);
				core->execution_three->sons[i]->heredoc_id = 1;
				fd = open("HEREDOC", O_WRONLY | O_CREAT | O_APPEND, 0644);
				char *buf = NULL;
				while (1)
				{
					buf = readline("heredoc> ");
					buf = ft_strjoin(buf, "\n");
					if (ft_strncmp(buf, path, ft_strlen(path)) == 0)
					{
						free(buf);
						break ;
					}
					ft_putstr_fd(buf, fd);
					free(buf);
				}
				close(fd);
			}
			if ((j + 1 < core->execution_three->sons_ctr) && ft_strncmp(core->execution_three->sons[j]->content, "GREAT", 5) == 0)
			{
				path = ft_substr(core->execution_three->sons[j + 1]->content, 1, ft_strlen(core->execution_three->sons[j + 1]->content) - 2);
				core->execution_three->sons[j]->content = "\0";
				core->execution_three->sons[j + 1]->content = "\0";
				core->execution_three->sons[i]->output_mode = 1;
				core->execution_three->sons[i]->output = ft_strdup(path);
				fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				close(fd);
			}
			if ((j + 1 < core->execution_three->sons_ctr) && ft_strncmp(core->execution_three->sons[j]->content, "LESS", 4) == 0)
			{
				path = ft_substr(core->execution_three->sons[j + 1]->content, 1, ft_strlen(core->execution_three->sons[j + 1]->content) - 2);
				core->execution_three->sons[j]->content = "\0";
				core->execution_three->sons[j + 1]->content = "\0";
				core->execution_three->sons[i]->input = ft_strdup(path);
			}
			j++;
		}
		i++;
	}
}
