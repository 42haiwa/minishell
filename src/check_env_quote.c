/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:15:41 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/12 19:05:34 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace(char *s, char *old, char *new)
{
	char	*find;
	int		old_len;
	int		new_len;
	int		new_size;
	char	*result;
	
	find = ft_strstr(s, old);
	if (find != NULL) {
		old_len = ft_strlen(old);
		new_len = ft_strlen(new);
		new_size = ft_strlen(s) - old_len + new_len;
		result = (char *)malloc(new_size + 1);
		ft_strncpy(result, s, find - s);
		result[find - s] = '\0';
		ft_strcat(result, new);
		ft_strcat(result, find + old_len);
		return (result);
	}
	return (ft_strdup(s));
}

int	is_ending(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' 
		|| c == '\r'
		|| c == '\t' || c == '\v');
}

char	**exctract_env(const char *chaine)
{
	int i = -1;
	int nbOccurrences = 0;

	while (chaine[++i] != '\0')
	{
		if (chaine[i] == '$')
			nbOccurrences++;
	}
	char **resultats = (char**)malloc(nbOccurrences * sizeof(char*));
	i = 0;
	int resultatIndex = 0;
	while (chaine[i] != '\0')
	{
		if (chaine[i] == '$')
		{
			i++;
			int j = 0;
			while (chaine[i] != '\0' && !is_ending(chaine[i]))
			{
				i++;
				j++;
			}
			resultats[resultatIndex] = (char*)malloc((j + 1) * sizeof(char));
			i -= j;
			j = 0;
			while (chaine[i] != '\0' && !is_ending(chaine[i]))
			{
				resultats[resultatIndex][j] = chaine[i];
				i++;
				j++;
			}
			resultats[resultatIndex][j] = '\0';
			resultatIndex++;
		}
		else
			i++;
	}
	return (resultats);
}
