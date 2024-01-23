/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:00:50 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/23 17:56:58 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_until(char const *s, char until, int is_include)
{
	size_t	dup_len;
	size_t	i;
	char	*dup;

	dup_len = 0;
	while (s[dup_len] != until)
		dup_len++;
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

void	rm_sep_three(t_node *root)
{
	int		i;
	char	*cpy;

	i = 0;
	if (root == NULL)
		return ;
	if (root->content != NULL && ft_strchr(root->content, '<')
		&& ft_strchr(root->content, '>'))
	{
		cpy = ft_substr(root->content, 1, ft_strlen(root->content) - 2);
		ft_strlcpy(root->content, cpy, ft_strlen(cpy) + 1);
		free(cpy);
	}
	while (i < root->sons_ctr)
	{
		rm_sep_three(root->sons[i]);
		i++;
	}
}

void	fill_three(t_core *core)
{
	size_t	i;
	t_node	*current;
	t_node	*father;

	i = -1;
	father = NULL;
	core->execution_three = node_init(ft_strdup(""));
	if (core->lexer_out == NULL)
		return ;
	while (core->lexer_out[++i])
	{
		if (core->lexer_out[i] == '<')
		{
			current = node_init(dup_until(core->lexer_out + i, '>', 1));
			if (father)
			{
				node_add_son(father, current);
			}
			else
			{
				node_add_son(core->execution_three, current);
				father = current;
			}
		}
		if (ft_strncmp(&core->lexer_out[i], "PIPE", 4) == 0)
		{
			current = node_init(ft_strdup("PIPE"));
			node_add_son(core->execution_three, current);
			father = NULL;
		}
		if (ft_strncmp(&core->lexer_out[i], "SEMICOLON", 9) == 0)
		{
			current = node_init(ft_strdup("SEMICOLON"));
			node_add_son(core->execution_three, current);
			father = NULL;
		}
		if (ft_strncmp(&core->lexer_out[i], "LESSLESS", 8) == 0)
		{
			current = node_init(ft_strdup("LESSLESS"));
			node_add_son(core->execution_three, current);
			father = NULL;
			i += 7;
		}
		if (ft_strncmp(&core->lexer_out[i], "GREATGREAT", 10) == 0)
		{
			current = node_init(ft_strdup("GREATGREAT"));
			node_add_son(core->execution_three, current);
			father = NULL;
			i += 9;
		}
		if (ft_strncmp(&core->lexer_out[i], "LESS", 4) == 0)
		{
			current = node_init(ft_strdup("LESS"));
			node_add_son(core->execution_three, current);
			father = NULL;
		}
		if (ft_strncmp(&core->lexer_out[i], "GREAT", 5) == 0)
		{
			current = node_init(ft_strdup("GREAT"));
			node_add_son(core->execution_three, current);
			father = NULL;
		}
	}
}

void	free_three(struct s_node *node)
{
	int	i;

	i = 0;
	if (node == NULL)
		return ;
	while (i < node->sons_ctr)
	{
		free_three(node->sons[i]);
		i++;
	}
	if (node->sons)
		free(node->sons);
	if (node->content)
	{
		free(node->content);
	}
	free(node);
}
