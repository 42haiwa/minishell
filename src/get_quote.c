/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:41:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/12 19:08:18 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// size_t	get_len_quote(const char *s, int *index, const char c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[*index + i] == c)
// 		(*index)++;
// 	while(s[*index + i] && s[*index + i] != c)
// 		i++;
// 	return (i);
// }

// char	*get_inside_quote(const char *s, int index, const char c)
// {
// 	char	*result;
// 	size_t	len;

// 	len = get_len(s, &index, c);
// 	if (len == 0)
// 		return (NULL);
// 	result = ft_calloc((len + 1), sizeof(char));
// 	if (!result)
// 		return (NULL);
// 	ft_strlcpy(result, s + index, len + 1);
// 	if (result[len] == '\'')
// 		result[len] = '\0';
// 	return (result);
// }

// size_t	get_number_quote(const char *buf)
// {
// 	size_t	i;
// 	size_t	count;
// 	int		boolean;

// 	if (ft_strchr(buf, 34) == NULL)
// 		return (0);
// 	count = 0;
// 	i = -1;
// 	boolean = 0;
// 	while (buf[++i])
// 	{
// 		if (buf[i] == 34)
// 		{
// 			if (boolean)
// 				boolean = 0;
// 			else
// 			{
// 				count++;
// 				boolean = 1;
// 			}
// 		}
// 	}
// 	return (count);
// }

// char	**get_quote(char *buf)
// {
// 	size_t	var[3];
// 	char	**result;
// 	size_t	quote_number;

// 	quote_number = get_number_quote(buf);
// 	if (quote_number == 0)
// 		return (NULL);
// 	result = ft_calloc(quote_number + 1, sizeof(char *));
// 	if (!result)
// 		return (NULL);
// 	var[0] = -1;
// 	var[1] = 0;
// 	var[2] = 0;
// 	while (buf[++var[0]])
// 	{
// 		if (buf[var[0]] == '\'')
// 		{
// 			if (!var[1])
// 			{
// 				result[var[2]] = get_inside(buf, var[0], '\'');
// 				var[2]++;
// 				var[1] = 1;
// 			} else {
// 				var[1] = 0;
// 			}
// 		}
// 	}
// 	result[var[2]] = 0;
// 	return (result);
// }
