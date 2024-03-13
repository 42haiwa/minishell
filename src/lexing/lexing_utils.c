/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:16:54 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/11 16:14:04 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_delimiter(char *token)
{
	if (ft_strncmp(token, "|", 1) == 0)
		return ("PIPE");
	if (ft_strncmp(token, ";", 1) == 0)
		return ("SEMICOLON");
	if (ft_strncmp(token, ">>", 2) == 0)
		return ("GREATGREAT");
	if (ft_strncmp(token, ">", 1) == 0)
		return ("GREAT");
	if (ft_strncmp(token, "<<", 2) == 0)
		return ("LESSLESS");
	if (ft_strncmp(token, "<", 1) == 0)
		return ("LESS");
	return (NULL);
}

void	add_block2(t_core *core, char *result)
{
	char	*save;

	if (core->lexer_out == NULL)
	{
		core->lexer_out = result;
		return ;
	}
	save = core->lexer_out;
	core->lexer_out = ft_strjoin(save, result);
	free(save);
	free(result);
}

void	add_block(const char *s, t_core *core, int delimiter)
{
	size_t	i;
	char	*result;

	if (!s)
		return ;
	if (!delimiter)
	{
		result = ft_calloc(ft_strlen(s) + 3, sizeof(char));
		i = 1;
		result[0] = START;
		while (s[i - 1])
		{
			result[i] = s[i - 1];
			i++;
		}
		result[i] = END;
		result[i + 1] = '\0';
	}
	else
		result = ft_strdup(s);
	add_block2(core, result);
}