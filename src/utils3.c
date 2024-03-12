/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 04:00:35 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/09 09:45:17 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*safe_join(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*result;
	
	if (!s1 && s2)
	{
		result = ft_strdup(s2);
		if (free_s2)
			free(s2);
		return (result);
	}
	if (s1 && !s2)
	{
		result = ft_strdup(s1);
		if (free_s1)
			free(s1);
		return (s1);
	}
	if (!s1 && !s2)
		return (ft_strdup(""));
	result = ft_strjoin(s1, s2);
	if(free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (result);
}

char	*get_substring(char *str, char c, int start_index)
{
	int		index;
	char	*substring;

	index = start_index;
	if (c != 0)
	{
		while (str[index] && str[index] != c)
			index++;
		substring = malloc(index - start_index + 2);
		ft_strncpy(substring, str + start_index, index - start_index + 1);
		substring[index - start_index] = '\0';
		return (substring);
	}
	while (str[index])
		index++;
	substring = malloc(index - start_index + 2);
	ft_strncpy(substring, str + start_index, index - start_index + 1);
	substring[index - start_index] = '\0';
	return (substring);
}

char	*get_string(char *buf, char start, int index)
{
	char	*current;
	char	*end;
	char	*result;
	int		len;

	current = buf + index;
	while (*current != '\0') 
	{
		if (*current == start)
			break;
		current++;
	}
	end = current + 1;
	while (*end != '\0')
	{
		if (is_ending(*end))
			break;
		end++;
	}
	len = end - current;
	result = (char*)ft_calloc((len + 1), sizeof(char));
	ft_strncpy(result, current, len);
	result[len] = '\0';
	return (result);
}

char	get_first(char *str, char *charset, size_t start)
{
	while (str[start])
	{
		if (is_charset(str[start], charset))
			return (str[start]);
		start++;
	}
	return (0);
}

char	*remove_char(char *str, int val)
{
	char	*tmp;
	
	tmp = strdup(str);
	while (str[val])
	{
		str[val] = tmp[val + 1];
		val++;
	}
	free(tmp);
	return (str);
}
