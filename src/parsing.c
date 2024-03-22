/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:00:50 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/22 18:21:28 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_until(char const *s, char until, int is_include)
{
	size_t	dup_len;
	size_t	i;
	char	*dup;

	dup_len = 0;
	while (s[dup_len] != until && s[dup_len] != '\0')
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
	if (root->content != NULL && ft_strchr(root->content, START)
		&& ft_strchr(root->content, END))
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
	if (core->lexer_out == NULL)
		return ;
	while (core->lexer_out[++i])
	{
		if (core->lexer_out[i] == START)
		{
			current = node_init(dup_until(core->lexer_out + i, END, 1));
			if (father)
				node_add_son(father, current);
			else
			{
				node_add_son(core->execution_three, current);
				father = current;
			}
		}
		verify_token(&i, &current, &father, core);
	}
	free(core->lexer_out);
	core->lexer_out = NULL;
}

void rprint_with_indentation(t_node *node, int depth)
{
    if (node == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf("\t");

    printf("Contenu : %s\n", (char *)node->content);

    if (node->sons != NULL)
	{
        for (ssize_t i = 0; i < node->sons_ctr; ++i)
		{
            rprint_with_indentation(node->sons[i], depth + 1);
        }
    }
}

void rprint(t_node *node)
{
    rprint_with_indentation(node, 0);
}

void	free_three(struct s_node **node)
{
	int	i;

	i = 0;
	if (*node == NULL)
		return ;
	while (i < (*node)->sons_ctr)
	{
		free_three(&(*node)->sons[i]);
		i++;
	}
	if ((*node)->sons)
		free((*node)->sons);
	if ((*node)->content)
		free((*node)->content);
	if ((*node)->output)
		free((*node)->output);
	if ((*node)->input)
		free((*node)->input);
	free(*node);
	*node = NULL;
}
