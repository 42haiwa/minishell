/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_lexing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:02:47 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/14 18:22:33 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var2(char **buf, t_core *core)
{
	if ((*buf)[core->lex_i] == '\'')
	{
		if (!core->lex_bool[D_QUOTE])
		{
			core->lex_bool[QUOTE] = !core->lex_bool[QUOTE];
			core->lex_bool[BOTH] = !core->lex_bool[BOTH];
		}
	}
	if ((*buf)[core->lex_i] == '\"')
	{
		if (!core->lex_bool[QUOTE])
			core->lex_bool[D_QUOTE] = !core->lex_bool[D_QUOTE];
	}
	if (((*buf)[core->lex_i] == '|' || (*buf)[core->lex_i] == ';' \
			|| (*buf)[core->lex_i] == '>' || (*buf)[core->lex_i] == '<') \
			&& !core->lex_bool[BOTH] && !core->lex_bool[D_QUOTE])
	{
		if ((*buf)[core->lex_i + 1] != ' ')
			*buf = add_char(*buf, ' ', core->lex_i + 1);
		if (core->lex_i > 0 && (*buf)[core->lex_i - 1] != ' ')
			*buf = add_char(*buf, ' ', core->lex_i);
	}
	
}

char	*replace_var(char *buf, t_core *core)
{
	char	*save;
	char	*tmp;

	core->lex_i = -1;
	core->lex_bool[BOTH] = 0;
	core->lex_bool[QUOTE] = 0;
	core->lex_bool[D_QUOTE] = 0;
	while (buf[++core->lex_i])
	{
		replace_var2(&buf, core);
		if (buf[core->lex_i] == ' ' \
			&& (core->lex_bool[BOTH] || core->lex_bool[D_QUOTE]))
				buf = remove_char(buf, core->lex_i--);
		if (buf[core->lex_i] == '$' && !core->lex_bool[BOTH])
		{
			save = get_string(buf, '$', core->lex_i);
			tmp = get_envp(ft_strchr(save, save[1]), core);
			buf = replace(buf, save, tmp);
			core->lex_i += ft_strlen(tmp) - 1;
			free(save);
		}
	}
	return (buf);
}

void	pre_lexing(char *buf, t_core *core)
{
	char	**splited;

	core->get_d_quote = get_double_quote(buf);
	core->get_quote = get_quote(buf);
	replace_main(core);
	buf = replace_var(buf, core);
	core->lex_bool[QUOTE] = 0;
	core->lex_bool[D_QUOTE] = 0;
	core->lex_bool[BOTH] = 0;
	core->lex_join = NULL;
	core->lex_count = 0;
	core->lex_count2 = 0;
	splited = ft_split(buf, ' ');
	lexing(splited, core);
	free_str_tab(splited);
	free(buf);
}
