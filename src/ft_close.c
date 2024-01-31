#include "minishell.h"

void    ft_close(int fd)
{
    if (fd != -1)
    {
        close(fd);
    }
}