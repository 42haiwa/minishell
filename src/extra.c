/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:40:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/26 17:17:20 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_buf(char *buf, size_t i)
{
	while (buf[++i])
	{
		if (buf[i] == '|' || buf[i] == ';')
			return (1);
		else if (buf[i] == ' ')
			continue ;
		else 
			return (0);
	}
	return (0);
}

char	*check_extra(char *buf)
{
	size_t	i;

	if (ft_strcmp(buf, "") == 0)
		return (NULL);
	if (ft_isonly(buf, " "))
		return (NULL);
	if (ft_isonly(buf, "<>|; "))
		return ("minishell: syntax error near unexpected token");
	if (ft_strlen(buf) > 1 && (buf[0] == '|'
			|| buf[0] == ';'))
		return ("minishell: syntax error near unexpected token");
	if (buf[ft_strlen(buf) - 1] == '|')
		return ("minishell: Pipe Error");
	if (buf[ft_strlen(buf) - 1] == '<' || buf[ft_strlen(buf) - 1] == '>')
		return ("minishell: syntax error near unexpected token");
	if (buf[ft_strlen(buf) - 1] == ';')
		return ("minishell: syntax error near unexpected token");
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '<')
		{
			if (check_buf(buf, i))
				return ("minishell: syntax error near unexpected token");
		}
	}
	return (NULL);
}
