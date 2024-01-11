/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:41:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/11 12:02:03 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_len(const char *s, int index, const char c)
{
	size_t	i;

	i = -1;
	while(s[++index])
	{
		i++;
		if (s[index] == c)
			break;
	}
	return (i);
}

char	*get_inside(const char *s, int index, const char c)
{
	char	*result;
	size_t	i;

	if (get_len(s, index, c) == 0)
		return (NULL);
	result = malloc((get_len(s, index, c) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[++index])
	{
		result[i] = s[index];
		if (s[index] == c)
			break;
		i++;
	}

	if (result[i] == 34)
		result[i] = '\0';
	return (result);
}

size_t	get_number_double_quote(const char *buf)
{
	size_t	i;
	size_t	count;
	int		boolean;

	if (ft_strchr(buf, 34) == NULL)
		return (0);
	count = 0;
	i = -1;
	boolean = 0;
	while (buf[++i])
	{
		if (buf[i] == 34)
		{
			if (boolean)
				boolean = 0;
			else
			{
				count++;
				boolean = 1;
			}
		}
	}
	return (count);
}

char	**get_double_quote(char *buf)
{
	size_t	var[3];
	char	**result;

	if (get_number_double_quote(buf) == 0)
		return (NULL);
	result = ft_calloc(get_number_double_quote(buf) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	var[0] = -1;
	var[1] = 0;
	var[2] = 0;
	while (buf[++var[0]])
	{
		if (buf[var[0]] == 34)
		{
			if (!var[1])
			{
				result[var[2]] = ft_calloc(get_len(buf, var[0], 34), sizeof(char));
				if (!result[var[2]])
					return (NULL);
				result[var[2]] = get_inside(buf, var[0], 34);
				var[2]++;
				var[1] = 1;
			} else {
				var[1] = 0;
			}
		}
	}
	result[var[2]] = 0;
	return (result);
}
