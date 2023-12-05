/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:22:30 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/05 19:26:28 by cjouenne         ###   ########.fr       */
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

void	lexing(char const *buf, t_core *core)
{
	size_t	i;
	char	*buf_w_delimiter;
	
	char	**buf_splited;

	buf_splited = ft_split(buf, ' ');
	i = -1;
	buf_w_delimiter = NULL;
	while (++i < ft_count_words(buf, ' '))
	{
		if (ft_strncmp(buf_splited[i], "|", 1) == 0)
		{
			buf_w_delimiter = ft_strjoin(buf_w_delimiter, "PIPE");
			continue ;
		}
		if (ft_strncmp(buf_splited[i], ";", 1) == 0)
		{
			buf_w_delimiter = ft_strjoin(buf_w_delimiter, "SEMICOLON");
			continue ;
		}
		if (ft_strncmp(buf_splited[i], ">", 1) == 0)
		{
			buf_w_delimiter = ft_strjoin(buf_w_delimiter, "GREAT");
			continue ;
		}
		if (ft_strncmp(buf_splited[i], ">>", 1) == 0)
		{
			buf_w_delimiter = ft_strjoin(buf_w_delimiter, "GREATGREAT");
			continue ;
		}
		if (ft_strncmp(buf_splited[i], "<", 1) == 0)
		{
			buf_w_delimiter = ft_strjoin(buf_w_delimiter, "LESS");
			continue ;
		}
		if (ft_strncmp(buf_splited[i], "<<", 1) == 0)
		{
			buf_w_delimiter = ft_strjoin(buf_w_delimiter, "LESSLESS");
			continue ;
		}
		if (buf_w_delimiter == NULL)
			buf_w_delimiter = ft_strjoin("", "<");
		else
			buf_w_delimiter = ft_strjoin(buf_w_delimiter, "<");
		buf_w_delimiter = ft_strjoin(buf_w_delimiter, buf_splited[i]);
		buf_w_delimiter = ft_strjoin(buf_w_delimiter, ">");
	}
	core->lexer_out = ft_strdup(buf_w_delimiter);
	printf("%s\n", buf_w_delimiter);
}
