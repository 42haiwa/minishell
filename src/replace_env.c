/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:15:41 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/17 21:46:35 by aallou-v         ###   ########.fr       */
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
	if (find != NULL)
	{
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
		|| c == '\r' || c == '$' || c == '\''
		|| c == '\t' || c == '\v' || c == '\"');
}

/*
var[0] = i
var[1] = j / occurence;
var[2] = result Index
*/

char	**exctract_env(const char *s)
{
	int		var[3];
	char	**result;

	var[0] = -1;
	var[1] = 0;
	while (s[++var[0]] != '\0')
		if (s[var[0]] == '$')
			var[1]++;
	result = (char **)ft_calloc((var[1] + 1), sizeof(char *));
	var[0] = 0;
	var[2] = 0;
	while (s[var[0]] != '\0')
	{
		if (s[var[0]] == '$')
		{
			var[0]++;
			var[1] = 0;
			while (s[var[0]] != '\0' && !is_ending(s[var[0]]))
			{
				var[0]++;
				var[1]++;
			}
			result[var[2]] = (char *)ft_calloc((var[1] + 1), sizeof(char));
			var[0] -= var[1];
			var[1] = 0;
			while (s[var[0]] != '\0' && !is_ending(s[var[0]]))
			{
				result[var[2]][var[1]] = s[var[0]];
				var[0]++;
				var[1]++;
			}
			result[var[2]][var[1]] = '\0';
			var[2]++;
		}
		else
			var[0]++;
	}
	return (result);
}

void	replace_main(t_core *core)
{
	size_t	i;
	size_t	j;
	char	**extract;

	i = -1;
	if (core->get_d_quote)
	{
		while (core->get_d_quote[++i])
		{
			extract = exctract_env(core->get_d_quote[i]);
			if (extract == NULL)
				continue ;
			j = -1;
			while (extract[++j])
			{
				core->get_d_quote[i] = replace(core->get_d_quote[i], "$", "");
				core->get_d_quote[i] = replace(core->get_d_quote[i],
						extract[j], get_envp(extract[j], core));
			}
		}
	}
}
