/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:38:31 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/13 14:22:19 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_getter(char *getter)
{
	if (!ft_contain(getter, &is_export_enable))
		return (0);
	if (ft_isdigit(getter[0]))
		return (0);
	return (1);
}