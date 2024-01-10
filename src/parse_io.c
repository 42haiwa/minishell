#include "minishell.h"

void	parse_io(t_core *core)
{
	int		i;
	char	*path;

	i = 0;
	while (i < core->execution_three->sons_ctr)
	{
		if (ft_strncmp(core->execution_three->sons[i]->content, "PIPE", 4) == 0)
		{
			i++;
			continue ;
		}
		if ((i + 2 < core->execution_three->sons_ctr) && ft_strncmp(core->execution_three->sons[i + 1]->content, "GREAT", 5) == 0
			&& ft_strncmp(core->execution_three->sons[i + 2]->content, "GREAT", 5) == 0)
		{
			path = ft_substr(core->execution_three->sons[i + 4]->content, 1, ft_strlen(core->execution_three->sons[i + 4]->content) - 2);
			printf("path: %s\n", path);
			core->execution_three->sons[i]->output_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			core->execution_three->sons[i + 1]->content = "\0";
			core->execution_three->sons[i + 2]->content = "\0";
			core->execution_three->sons[i + 3]->content = "\0";
			core->execution_three->sons[i + 4]->content = "\0";
			break ;
		}
		if ((i + 1 < core->execution_three->sons_ctr) && ft_strncmp(core->execution_three->sons[i + 1]->content, "GREAT", 5) == 0)
		{
			path = ft_substr(core->execution_three->sons[i + 2]->content, 1, ft_strlen(core->execution_three->sons[i + 2]->content) - 2);
			core->execution_three->sons[i]->output_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			core->execution_three->sons[i + 1]->content = "\0";
			core->execution_three->sons[i + 2]->content = "\0";
			break ;
		}
		i++;
	}
}
