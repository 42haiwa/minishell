/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing2_old_old.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:36:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/08 10:07:18 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_lexing(t_core *core, char *buf)
{
	char	*save;
	char	*tmp;
	
	core->lex_count = 0;
	core->lex_count2 = 0;
	core->lex_bool[QUOTE] = 0;
	core->lex_bool[D_QUOTE] = 0;
	core->lex_join = NULL;
	core->lex_i = -1;
	while(buf[++core->lex_i])
	{
		if (buf[core->lex_i] == '$')
		{
			save = get_string(buf, '$');
			tmp = get_envp(ft_strchr(save, save[1]), core);
			buf = replace(buf, save, tmp);
			core->lex_i += ft_strlen(tmp) - 1;
			free(save);
		}
	}
	return (buf);
}

void    recursive_lexing(char *splited, t_core *core)
{
	if (!core->lex_bool[QUOTE] && !core->lex_bool[D_QUOTE])
	{
		if (splited[0] != '\'' && splited[0] != '\"')
		{
			
		}
		else
		{
			if (splited[0] != '\'')
			{
				core->lex_bool[QUOTE] = 1;
				core->lex_join = safe_join(core->lex_join, core->get_quote[core->lex_count]);
				core->lex_count++;
			}
			if (splited[0] != '\"')
			{
				core->lex_bool[D_QUOTE] = 1;
				core->lex_join = safe_join(core->lex_join, core->get_d_quote[core->lex_count2]);
				core->lex_count2++;
			}
		}
	}
	else
	{
		
	}
}
