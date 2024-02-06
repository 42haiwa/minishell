/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_add_son.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:18:39 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/31 17:39:21 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_add_son2(t_node **father, t_node **sons_bck, t_node *neww)
{
	if (!((*father)->sons))
		return ;
	ft_memmove((*father)->sons, sons_bck, (*father)->sons_ctr
		* sizeof(t_node *));
	(*father)->sons[(*father)->sons_ctr] = neww;
	++((*father)->sons_ctr);
	free(sons_bck);
}

void	node_add_son(t_node *father, t_node *neww)
{
	t_node	**sons_bck;

	if (father)
	{
		if (father->sons == NULL)
		{
			father->sons = ft_calloc(1, sizeof(t_node *));
			if (!(father->sons))
				return ;
			*(father->sons) = neww;
			++(father->sons_ctr);
		}
		else
		{
			sons_bck = ft_calloc(father->sons_ctr, sizeof(t_node *));
			if (!(sons_bck))
				return ;
			ft_memmove(sons_bck, father->sons,
				father->sons_ctr * sizeof(t_node *));
			free(father->sons);
			father->sons = ft_calloc(father->sons_ctr + 1, sizeof(t_node *));
			node_add_son2(&father, sons_bck, neww);
		}
	}
}
