/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:00:50 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/07 15:54:59 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *dup_until(char const *s, char until, int is_include)
{
	size_t	dup_len;
	size_t	i;
	char	*dup;

	dup_len = 0;
	while (s[dup_len] != until)
	{
		dup_len++;
	}
	dup = ft_calloc(1, dup_len + 2);
	if (!dup)
		return (NULL);
	i = -1;
	while (s[++i])
	{
		dup[i] = s[i];
		if (dup[i] == until && is_include)
		{
			dup[i] = s[i];
			break ;
		}
		if (dup[i] == until && !is_include)
			break ;
	}
	i++;
	dup[i] = '\0';
	return (dup);
}

void	fill_three(t_core *core)
{
	size_t	i;
	int		is_cmd;
	t_node	*current;

	i = -1;
	is_cmd = 0;
	core->execution_three = node_init("");
	while (core->lexer_out[++i])
	{
		if (core->lexer_out[i] == '<')
		{
			current = node_init(dup_until(core->lexer_out + i, '>', 1));
			node_add_son(core->execution_three, current);
		}
		if (ft_strncmp(&core->lexer_out[i], "PIPE", 4) == 0)
		{
			current = node_init("PIPE");
			node_add_son(core->execution_three, current);
		}
		if (ft_strncmp(&core->lexer_out[i], "SEMICOLON", 9) == 0)
		{
			current = node_init("SEMICOLON");
			node_add_son(core->execution_three, current);
		}
		if (ft_strncmp(&core->lexer_out[i], "LESSLESS", 8) == 0)
		{
			current = node_init("LESSLESS");
			node_add_son(core->execution_three, current);
		}
		if (ft_strncmp(&core->lexer_out[i], "GREATGREAT", 10) == 0)
		{
			current = node_init("GREATGREAT");
			node_add_son(core->execution_three, current);
		}
		if (ft_strncmp(&core->lexer_out[i], "LESS", 4) == 0)
		{
			current = node_init("LESS");
			node_add_son(core->execution_three, current);
		}
		if (ft_strncmp(&core->lexer_out[i], "GREAT", 5) == 0)
		{
			current = node_init("GREAT");
			node_add_son(core->execution_three, current);
		}
	}
}
