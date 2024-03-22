/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:02:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/22 18:16:42 by aallou-v         ###   ########.fr       */
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

int	ft_contain_charset(char *str, char *c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (is_charset(str[i], c))
			return (1);
	}
	return (0);
}

int	ft_contain(char *str, int(*f)(char))
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!f(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_export_enable(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}
