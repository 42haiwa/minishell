/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:00:05 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/01 14:02:47 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_three	*three_init(void *content)
{
	t_three *current;

	current = ft_calloc(1, sizeof(t_three));
	if (!current)
		return (NULL)
	current->content = content;
	current->nodes = NULL;
	return (current);
}
