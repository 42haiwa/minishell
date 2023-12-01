/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:17:50 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 16:18:14 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*node_init(void *content)
{
	t_node	*node;

	node = calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->sons_ctr = 0;
	node->sons = NULL;
	return (node);
}
