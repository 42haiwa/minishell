/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:15:41 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/22 18:18:21 by aallou-v         ###   ########.fr       */
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
		free(s);
		return (result);
	}
	return (s);
}

/*
i = i
j = occurence / j
val = result Index
*/

void	extract_env2(t_repl	*stru, const char *s, char **result)
{
	stru->i++;
	stru->j = 0;
	while (s[stru->i] != '\0' && (!is_ending(s[stru->i])
			|| s[stru->i] != '$' || s[stru->i] != '?'))
	{
		stru->i++;
		stru->j++;
	}
	result[stru->val] = (char *)ft_calloc((stru->j + 1), sizeof(char));
	stru->i -= stru->j;
	stru->j = 0;
	while (s[stru->i] != '\0' && (!is_ending(s[stru->i])
			|| s[stru->i] != '$' || s[stru->i] != '?'))
	{
		result[stru->val][stru->j] = s[stru->i];
		stru->i++;
		stru->j++;
	}
	result[stru->val][stru->j] = '\0';
	stru->val++;
}

char	**exctract_env(const char *s)
{
	t_repl	stru;
	char	**result;

	stru.i = -1;
	stru.occurence = 0;
	while (s[++stru.i] != '\0')
		if (s[stru.i] == '$')
			stru.occurence++;
	if (stru.occurence == 0)
		return (NULL);
	result = (char **)ft_calloc((stru.occurence + 1), sizeof(char *));
	stru.i = 0;
	stru.val = 0;
	while (s[stru.i] != '\0')
	{
		if (s[stru.i] == '$')
			extract_env2(&stru, s, result);
		else
			stru.i++;
	}
	return (result);
}

void	replace_main(t_core *core)
{
	size_t	i;
	size_t	j;
	char	**extract;

	i = -1;
	extract = NULL;
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
			free_str_tab(extract);
		}
	}
}
