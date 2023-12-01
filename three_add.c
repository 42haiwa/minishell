/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:03:04 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 14:11:08 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	three_add(t_three *father, t_three *son)
{
	t_three	*current;
	t_three	*sons_bck;

	if (father)
	{
		if (father->nodes)
		{
			sons_bck = malloc(sizeof(father->nodes));
			if (!sons_bck)
				return ;
			ft_memmove(sons_bck, father->nodes, sizeof(father->nodes));
			free(father->nodes
		}	
	}
}
