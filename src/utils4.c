/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:02:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/09 13:07:35 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_by_char(char *str, char c, size_t start)
{
	int	i;

	i = 0;
	if (!str || ft_strlen(str) <= start)
		return (0);
	while (str[start])
	{
		i++;
		if (str[start++] == c)
			break ;
	}
	return (i);
}