/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_add_son.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:18:39 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 16:18:57 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_add_son(t_node *father, t_node *neww)
{
	t_node	**sons_bck;

	if (father)
	{
		if (father->sons == NULL)
		{
			father->sons = calloc(1, sizeof(t_node*));
			if (!(father->sons))
				return ;
			*(father->sons) = neww;
			++(father->sons_ctr);
		}
		else
		{
			sons_bck = calloc(father->sons_ctr, sizeof(t_node*));
			if (!(sons_bck))
				return ;
			memmove(sons_bck, father->sons, father->sons_ctr * sizeof(t_node*));
			father->sons = calloc(father->sons_ctr + 1, sizeof(t_node*));
			if (!(father->sons))
				return ;
			memmove(father->sons, sons_bck, father->sons_ctr
				* sizeof(t_node*));
			father->sons[father->sons_ctr] = neww;
			++(father->sons_ctr);
		}
	}
}
