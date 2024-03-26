/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 04:00:35 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/26 18:59:54 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ending(char c)
{
	if (ft_isalnum(c))
		return (0);
	if (c == '_')
		return (0);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	get_n_char(const char *s1, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s1[++i])
	{
		if (s1[i] == c)
			count++;
	}
	return (count);
}

int	is_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
	{
		if (c == charset[i])
			return (1);
	}
	return (0);
}

char	*ft_strcspn(char* str, char *charset)
{
	int		len;
	char	*new_str;

	len = 0;
	while (str[len] != '\0' && is_charset(str[len], charset))
		len++;
    new_str = ft_calloc(len + 1, 1);
	if (new_str == NULL)
		return NULL;
	ft_strncpy(new_str, str, len);
	new_str[len] = '\0';
	return new_str;
}
