/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:40:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/19 13:18:53 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_extra(char *buf)
{
	if (ft_strcmp(buf, "") == 0)
		return (NULL);
	if (ft_isonly(buf, "<>|;"))
		return ("minishell: syntax error near unexpected token");
	if (ft_strlen(buf) > 1 && (buf[0] == '|' || buf[0] == '<' || buf[0] == '>'
			|| buf[0] == ';'))
		return ("minishell: syntax error near unexpected token");
	if (buf[ft_strlen(buf) - 1] == '|')
		return ("minishell: Pipe Error");
	if (buf[ft_strlen(buf) - 1] == '<' || buf[ft_strlen(buf) - 1] == '>')
		return ("minishell: syntax error near unexpected token");
	if (buf[ft_strlen(buf) - 1] == ';')
		return ("minishell: syntax error near unexpected token");
	return (NULL);
}
