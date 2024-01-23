/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:36:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/01/17 15:54:16 by aallou-v         ###   ########.fr       */
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
	char	*save;

	if (!s)
		return ;
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
		result = ft_strdup(s);
	if (core->lexer_out == NULL)
	{
		core->lexer_out = ft_strdup(result);
		free(result);
		return ;
	}
	save = ft_strdup(core->lexer_out);
	free(core->lexer_out);
	core->lexer_out = ft_strjoin(save, result);
	free(save);
	free(result);
}

void	lexing(char *buf, t_core *core)
{
	size_t	i;
	char	**splited;
	size_t	count;
	size_t	count2;
	int		boolean[2];

	splited = ft_split(buf, ' ');
	count = 0;
	count2 = 0;
	boolean[0] = 0;
	boolean[1] = 0;
	i = -1;
	while (splited[++i])
	{
		if (splited[i][0] == '\"' && !boolean[0] && !boolean[1])
		{
			add_block(core->get_d_quote[count], core, 0);
			boolean[0] = 1;
			count++;
			if (splited[i][ft_strlen(splited[i]) - 1] == '\"' && ft_strlen(splited[i]) > 1)
				boolean[0] = 0;
		}
		else if (splited[i][0] == '\'' && !boolean[1] && !boolean[0])
		{
			add_block(core->get_quote[count2], core, 0);
			boolean[1] = 1;
			count2++;
			if (splited[i][ft_strlen(splited[i]) - 1] == '\'' && ft_strlen(splited[i]) > 1)
				boolean[1] = 0;
		}
		else
		{
			if (!boolean[0] && !boolean[1])
			{
				if (get_delimiter(splited[i]))
					add_block(get_delimiter(splited[i]), core, 1);
				else
				{
					if (splited[i][0] != '$')
						add_block(splited[i], core, 0);
					else
						add_block(get_envp(ft_strchr(splited[i], splited[i][1]), core), core, 0);
				}
			}
			else
			{
				if(splited[i][ft_strlen(splited[i]) - 1] == '\"')
					boolean[0] = 0;
				if(splited[i][ft_strlen(splited[i]) - 1] == '\'')
					boolean[1] = 0;
			}
		}
	}
	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;		
	}
	free(splited);
}

void	pre_lexing(char *buf, t_core *core)
{
	size_t	i;

	core->get_d_quote = get_double_quote(buf, core);
	core->get_quote = get_quote(buf);
	replace_main(core);
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '|' || buf[i] == ';' || buf[i] == '\"'
			|| buf[i] == '>' || buf[i] == '<' || buf[i] == '\'')
		{
			if (buf[i + 1] != ' ')
				buf = add_char(buf, ' ', i + 1);
			if (buf[i - 1] != ' ')
				buf = add_char(buf, ' ', i);
		}
		if (buf[i] == '$')
		{
			if (buf[i - 1] != ' ')
				buf = add_char(buf, ' ', i);
		}
	}
	lexing(buf, core);
}
