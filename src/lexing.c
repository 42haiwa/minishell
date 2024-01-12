/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:36:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/12 19:12:01 by aallou-v         ###   ########.fr       */
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

void	add_block(const char *s, t_core *core, int delimiter)
{
	size_t	i;
	char	*result;

	if (!delimiter)
	{
		result = ft_calloc(ft_strlen(s) + 3, sizeof(char));
		i = 1;
		result[0] = '<';
		while (s[i - 1])
		{
			result[i] = s[i - 1];
			i++;
		}
		result[i] = '>';
		result[i + 1] = '\0';
	}
	else
	{
		result = ft_strdup(s);
	}
	core->lexer_out = ft_strjoin(core->lexer_out, result);
	free(result);
}

void	lexing(char *buf, t_core *core)
{
	size_t	i;
	char	**splited;
	size_t	count;
	int		boolean;

	splited = ft_split(buf, ' ');
	i = -1;
	count = 0;
	boolean = 0;
	while (splited[++i])
	{
		if (splited[i][0] == '\"' && !boolean)
		{
			add_block(core->get_d_quote[count], core, 0);
			boolean = 1;
			count++;
			if (splited[i][ft_strlen(splited[i]) - 1] == '\"')
				boolean = 0;
		}
		else
		{
			if (!boolean)
			{
				if (get_delimiter(splited[i]))
					add_block(get_delimiter(splited[i]), core, 1);
				else
					add_block(splited[i], core, 0);
			}
			else
			{
				if(splited[i][ft_strlen(splited[i]) - 1] == '\"')
					boolean = 0;
			}
		}
	}
}

void	pre_lexing(char *buf, t_core *core)
{
	size_t	i;

	core->lexer_out = "";
	core->get_d_quote = get_double_quote(buf);
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '|' || buf[i] == ';' || buf[i] == '>' || buf[i] == '<')
		{
			if (buf[i + 1] != ' ')
				buf = add_char(buf, ' ', i + 1);
			if (buf[i - 1] != ' ')
				buf = add_char(buf, ' ', i);
		}
	}
	lexing(buf, core);
	ft_putendl_fd(core->lexer_out, 1);
}
