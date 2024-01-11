#include "minishell.h"

void	parse_io(t_core *core)
{
	int		i;
	int		j;
	char	*path;
	int		fd;

	(void) path;
	(void) j;
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
		i += j + 1;
	}
}
