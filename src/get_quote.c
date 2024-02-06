/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:41:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/07 00:32:44 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_inside_quote(const char *s, int index, const char c)
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
	if (result[len] == '\'')
		result[len] = '\0';
	return (result);
}

void	get_number_next(const char *buf, t_count *val)
{
	if (buf[val->i] == '\'' && !val->boolean[1])
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

size_t	get_number_quote(const char *buf)
{
	t_count	val;

	if (ft_strchr(buf, '\'') == NULL)
		return (0);
	val.count = 0;
	val.i = -1;
	val.boolean[0] = 0;
	val.boolean[1] = 0;
	while (buf[++val.i])
	{
		if (buf[val.i] == '\"')
		{
			if (val.boolean[1])
				val.boolean[1] = 0;
			else
				val.boolean[1] = 1;
		}
		get_number_next(buf, &val);
	}
	return (val.count);
}

void	second_part_quote(t_quote *stru, char *buf, char **result)
{
	if (buf[stru->var[0]] == '\'' && !stru->boolean[1])
	{
		if (!stru->boolean[0])
		{
			result[stru->var[1]] = get_inside_quote(buf, stru->var[0], '\'');
			stru->var[1]++;
			stru->boolean[0] = 1;
		}
		else
			stru->boolean[0] = 0;
	}
}

char	**get_quote(char *buf)
{
	t_quote	stru;
	char	**result;

	stru.quote_number = get_number_quote(buf);
	if (stru.quote_number == 0)
		return (NULL);
	result = ft_calloc(stru.quote_number + 1, sizeof(char *));
	if (!result)
		return (NULL);
	stru.var[0] = -1;
	stru.var[1] = 0;
	stru.boolean[0] = 0;
	stru.boolean[1] = 0;
	while (buf[++stru.var[0]])
	{
		if (buf[stru.var[0]] == '\"')
		{
			if (stru.boolean[1])
				stru.boolean[1] = 0;
			else
				stru.boolean[1] = 1;
		}
		second_part_quote(&stru, buf, result);
	}
	return (result[stru.var[1]] = 0, result);
}
