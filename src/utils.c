/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 23:07:05 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/06 18:46:13 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_char(char *s, char c, int index)
{
	char	*result;
	int		i;

	result = ft_calloc((ft_strlen(s) + 2), sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (s[++i] && i != index)
		result[i] = s[i];
	result[i] = c;
	while (s[i])
	{
		result[i + 1] = s[i];
		i++;
	}
	result[i + 1] = '\0';
	free(s);
	return (result);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == 0)
		return (str);
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (str[i + j] == to_find[j] && to_find[j])
				j++;
			if (to_find[j] == 0)
				return (&str[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (dest[i] != '\0')
		i++;
	while (src[i2] != '\0')
	{
		dest[i] = src[i2];
		i++;
		i2++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	get_len(const char *s, int *index, const char c)
{
	size_t	i;

	i = 0;
	while (s[*index + i] == c)
		(*index)++;
	while (s[*index + i] && s[*index + i] != c)
		i++;
	return (i);
}
