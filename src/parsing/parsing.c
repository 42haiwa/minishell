/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:18:51 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/25 17:44:45 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **split_buf(char const *buf)
{
    char    *buf_sep;
    char    **splited;
    size_t  i;

    i = -1;
    buf_sep = ft_calloc(sizeof(char), ft_strlen(buf) + 1);
    while (buf[++i])
    {
        buf_sep[i] = buf[i];
        if (buf[i] == START || buf[i] == END)
            buf_sep[i] = START;
    }
    splited = ft_split(buf_sep, START);
    return (splited);
}

static int  check_redirect(char **split, size_t const i)
{
    if (i >= 1 && split[i - 1])
    {
        if (ft_strcmp(split[i - 1], "GREAT") == 0)
            return (1);
        if (ft_strcmp(split[i - 1], "GREATGREAT") == 0)
            return (1);
        if (ft_strcmp(split[i - 1], "LESS") == 0)
            return (1);
        if (ft_strcmp(split[i - 1], "LESSLESS") == 0)
            return (1);
    }
    return (0);
}

static void parse_io_n(t_core *core, size_t lpipe, t_node *current, char ** splited)
{
    size_t  i;

    i = lpipe + 1;
    if (!lpipe)
        i = 0;
    while (splited[i] && ft_strcmp(splited[i], "PIPE") != 0)
    {
        if (ft_strcmp(splited[i], "GREAT") == 0)
        {
            current->output = ft_strdup(splited[i + 1]);
            current->output_mode = 1;
		    close(open(current->output, O_WRONLY | O_CREAT | O_TRUNC, 0644));
        }
        if (ft_strcmp(splited[i], "GREATGREAT") == 0)
        {
            current->output = ft_strdup(splited[i + 1]);
            current->output_mode = 2;
		    close(open(current->output, O_WRONLY | O_CREAT | O_APPEND, 0644));
        }
        i++;
    }
    i--;
    while (i >= 1 && ft_strcmp(splited[i], "PIPE"))
    {
        if (ft_strcmp(splited[i], "LESS") == 0)
            current->input = ft_strdup(splited[i + 1]);
        i--;
    }
}

void    bill_three(t_core *core)
{
    char    **splited;
    size_t  i;
    t_node  *father;
    t_node  *current;
    size_t  last_pipe;
    size_t  last_cmd;

    i = -1;
    splited = split_buf(core->lexer_out);
    core->cmd_p = 0;
    last_pipe = 0;
    last_cmd = 0;
    father = NULL;
    while (splited[++i])
    {
        if (ft_strcmp(splited[i], "PIPE") == 0)
        {
            father = NULL;
            node_add_son(core->execution_three, node_init(ft_strdup(splited[i])));
            core->cmd_p = 0;
            last_pipe = i;
            continue ;
        }
        if (!check_redirect(splited, i) && !is_token(splited[i]))
        {
            current = node_init(ft_strdup(splited[i]));
            if (!core->cmd_p)
            {
                last_cmd = i;
                parse_io_n(core, last_pipe, current, splited);
            }
            if (father)
                node_add_son(father, current);
            else
            {
                node_add_son(core->execution_three, current);
                father = current;
            }
            core->cmd_p = 1;
        }
    }
    free(core->lexer_out);
    core->lexer_out = NULL;
}