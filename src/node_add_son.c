/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_add_son.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:18:39 by cjouenne          #+#    #+#             */
/*   Updated: 2024/02/10 22:05:54 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_add_son(t_node *father, t_node *neww)
{
	t_node	**new_sons;

	if (father)
	{
		if (father->sons == NULL)
		{
			father->sons = ft_calloc(1, sizeof(t_node *));
			if (!father->sons)
				return ;
			father->sons[0] = neww;
			father->sons_ctr++;
		}
		else
		{
			new_sons = ft_calloc(father->sons_ctr + 1, sizeof(t_node *));
			if (!new_sons)
				return ;
			ft_memmove(new_sons, father->sons,
				father->sons_ctr * sizeof(t_node *));
			free(father->sons);
			new_sons[father->sons_ctr] = neww;
			father->sons_ctr++;
			father->sons = new_sons;
		}
	}
}
