/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_d_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:41:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/16 15:11:20 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_len(const char *s, int *index, const char c)
{
	size_t	i;

	i = 0;
	while (s[*index + i] == c)
		(*index)++;
	while(s[*index + i] && s[*index + i] != c)
		i++;
	return (i);
}

char	*get_inside(const char *s, int index, const char c)
{
	char	*result;
	size_t	len;

	len = get_len(s, &index, c);
	if (len == 0)
		return (NULL);
	result = ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + index, len + 1);
	if (result[len] == '\"')
		result[len] = '\0';
	return (result);
}

size_t	get_number_double_quote(const char *buf)
{
	size_t	i;
	size_t	count;
	int		boolean[2];

	if (ft_strchr(buf, '\"') == NULL)
		return (0);
	count = 0;
	i = -1;
	boolean[0] = 0;
	boolean[1] = 0;
	while (buf[++i])
	{
		if (buf[i] == '\'')
		{
			if (boolean[1])
				boolean[1] = 0;
			else
				boolean[1] = 1;
		}
		if (buf[i] == '\"' && !boolean[1])
		{
			if (boolean[0])
				boolean[0] = 0;
			else
			{
				count++;
				boolean[0] = 1;
			}
		}
	}
	return (count);
}

char	**get_double_quote(char *buf, t_core *core)
{
	size_t	var[2];
	int		boolean[2];
	char	**result;
	size_t	double_quote_number;

	(void) core;
	double_quote_number = get_number_double_quote(buf);
	if (double_quote_number == 0)
		return (NULL);
	result = ft_calloc(double_quote_number + 1, sizeof(char *));
	if (!result)
		return (NULL);
	var[0] = -1;
	var[1] = 0;
	boolean[0] = 0;
	boolean[1] = 0;
	while (buf[++var[0]])
	{
		if (buf[var[0]] == '\'')
		{
			if (boolean[1])
				boolean[1] = 0;
			else
				boolean[1] = 1;
		}
		if (buf[var[0]] == '\"' && !boolean[1])
		{
			if (!boolean[0])
			{
				result[var[1]] = get_inside(buf, var[0], '\"');
				var[1]++;
				boolean[0] = 1;
			}
			else
				boolean[0] = 0;
		}
	}
	result[var[1]] = 0;
	return (result);
}
