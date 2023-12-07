/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 23:07:05 by aallou-v          #+#    #+#             */
/*   Updated: 2023/12/07 23:14:31 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_char(const char *s, char c, int index)
{
	char	*result;
	int		i;

	result = malloc((ft_strlen(s) + 2) * sizeof(char));
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
	return (result);
}