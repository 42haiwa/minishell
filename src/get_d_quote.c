/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_d_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:41:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/09 14:39:47 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_inside(const char *s, int index, const char c)
{
	char	*result;
	size_t	len;

	if (s[index + 1] == '\"' || s[index + 1] == '\0')
		return (ft_strdup(""));
	len = get_len(s, &index, c);
	if (len == 0)
		return (ft_strdup(""));
	result = ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + index, len + 1);
	if (result[len] == '\"')
		result[len] = '\0';
	return (result);
}

void	next_get_number(const char *buf, t_d_count *val)
{
	if (buf[val->i] == '\"' && !val->boolean[1])
	{
		if (val->boolean[0])
			val->boolean[0] = 0;
		else
		{
			val->count++;
			val->boolean[0] = 1;
		}
	}
}

size_t	get_number_double_quote(const char *buf)
{
	t_d_count	val;

	if (ft_strchr(buf, '\"') == NULL)
		return (0);
	val.count = 0;
	val.i = -1;
	val.boolean[0] = 0;
	val.boolean[1] = 0;
	while (buf[++val.i])
	{
		if (buf[val.i] == '\'')
		{
			if (val.boolean[1])
				val.boolean[1] = 0;
			else
				val.boolean[1] = 1;
		}
		next_get_number(buf, &val);
	}
	return (val.count);
}

void	second_part(t_d_quote *stru, char *buf, char **result)
{
	if (buf[stru->var[0]] == '\"' && !stru->boolean[1])
	{
		if (!stru->boolean[0])
		{
			result[stru->var[1]] = get_inside(buf, stru->var[0], '\"');
			stru->var[1]++;
			stru->boolean[0] = 1;
		}
		else
			stru->boolean[0] = 0;
	}
}

char	**get_double_quote(char *buf)
{
	char		**result;
	t_d_quote	stru;

	stru.double_quote_number = get_number_double_quote(buf);
	if (stru.double_quote_number == 0)
		return (NULL);
	stru.var[0] = -1;
	stru.var[1] = 0;
	stru.boolean[0] = 0;
	stru.boolean[1] = 0;
	result = ft_calloc(stru.double_quote_number * 2 + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (buf[++stru.var[0]])
	{
		if (buf[stru.var[0]] == '\'')
		{
			if (stru.boolean[1])
				stru.boolean[1] = 0;
			else
				stru.boolean[1] = 1;
		}
		second_part(&stru, buf, result);
	}
	return (result[stru.var[1]] = 0, result);
}
