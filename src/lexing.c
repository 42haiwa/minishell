/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:22:30 by cjouenne          #+#    #+#             */
/*   Updated: 2024/01/11 12:06:57 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	ctr;
	size_t	last;

	i = -1;
	ctr = 0;
	last = 1;
	while (s[++i])
	{
		if (last && s[i] != c)
		{
			last = 0;
			ctr++;
		}
		else if (!last && s[i] == c)
			last = 1;
	}
	return (ctr);
}

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

char	*end_lexing(char *buf_w, char *split)
{
	char	*tmp;

	if (buf_w == NULL)
		buf_w = ft_strjoin("", "<");
	else
	{
		tmp = buf_w;
		buf_w = ft_strjoin(tmp, "<");
		free(tmp);
	}
	tmp = buf_w;
	buf_w = ft_strjoin(tmp, split);
	free(tmp);
	tmp = buf_w;
	buf_w = ft_strjoin(tmp, ">");
	free(tmp);
	return (buf_w);
}

void	lexing(char *buf, t_core *core)
{
	size_t	i;
	char	*buf_w_delimiter;
	char	*tmp;
	char	**buf_splited;
	char	*delimiter;

	buf_splited = ft_split(buf, ' ');
	i = -1;
	buf_w_delimiter = NULL;
	while (++i < ft_count_words(buf, ' '))
	{
		delimiter = get_delimiter(buf_splited[i]);
		if (delimiter)
		{
			tmp = buf_w_delimiter;
			buf_w_delimiter = ft_strjoin(tmp, delimiter);
			free(tmp);
			continue ;
		}
		tmp = buf_w_delimiter;
		buf_w_delimiter = end_lexing(tmp, buf_splited[i]);
		//free(tmp);
	}
	core->lexer_out = ft_strdup(buf_w_delimiter);
}

void	pre_lexing(char *buf, t_core *core)
{
	int		i;

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
}
