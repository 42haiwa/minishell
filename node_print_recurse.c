/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_print_recurse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:20 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 16:19:34 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_print_recurse(t_node *root)
{
	int	i = 0;
	if (root == NULL)
		return ;
	printf("%s\n", (char *) root->content);
	while (i < root->sons_ctr)
	{
		node_print_recurse(root->sons[i]);
		i++;
	}
}
