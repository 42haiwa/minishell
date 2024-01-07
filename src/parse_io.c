#include "minishell.h"

void	parse_io(t_core *core)
{
	int	i;
	int	j;
	int		fd;
	char	*path;

	i = 0;
	while (i < core->execution_three->sons_ctr)
	{
		j = i;
		if (ft_strncmp(core->execution_three->sons[i]->content, "GREATGREAT", 10) == 0)
		{
			path = ft_substr(core->execution_three->sons[i + 2]->content, 1, ft_strlen(core->execution_three->sons[i + 2]->content) - 2);
			fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 777);
			core->execution_three->sons[i]->content = ft_strdup("\0");
			core->execution_three->sons[i + 1]->content = ft_strdup("\0");
			while (j >= 0 && core->execution_three->sons[j])
			{
				if (ft_strncmp(core->execution_three->sons[j]->content, "\0", 1) != 0)
					core->execution_three->sons[j]->output_fd = fd;
				j--;
			}
			break ;
		}
		if (ft_strncmp(core->execution_three->sons[i]->content, "GREAT", 5) == 0)
		{
			path = ft_substr(core->execution_three->sons[i + 1]->content, 1, ft_strlen(core->execution_three->sons[i + 1]->content) - 2);
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 777);
			core->execution_three->sons[i]->content = ft_strdup("\0");
			core->execution_three->sons[i + 1]->content = ft_strdup("\0");
			while (j >= 0 && core->execution_three->sons[j])
			{
				if (ft_strncmp(core->execution_three->sons[j]->content, "\0", 1) != 0)
					core->execution_three->sons[j]->output_fd = fd;
				j--;
			}
			break ;
		}
		i++;
	}
}
