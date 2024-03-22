/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:02:20 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/22 19:32:01 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexing3(char **splited, t_core *core)
{
	core->first = get_first(splited[core->lex_i], "\'\"", core->lex_x);
	core->substr = get_substring(splited[core->lex_i], core->first, core->lex_x);
	core->lex_join = safe_join(core->lex_join, core->substr, 0, 0);
	core->lex_x += len_by_char(splited[core->lex_i], core->first, core->lex_x);
}

void	lexing2(char **splited, t_core *core)
{
	while (1)
	{
		lexing3(splited, core);
		if (core->first == 0)
			break ;
		if (core->first == '\'')
		{
			core->lex_join = safe_join(core->lex_join, core->get_quote[core->lex_count], 0, 0);
			if (core->get_quote[core->lex_count])
				core->lex_x += ft_strlen(core->get_quote[core->lex_count]) + 1;
			else
				core->lex_x += 2;
			core->lex_count++;
		}
		if (core->first == '\"')
		{
			core->lex_join = safe_join(core->lex_join, core->get_d_quote[core->lex_count2], 0, 0);
			if (core->get_d_quote[core->lex_count2])
				core->lex_x += ft_strlen(core->get_d_quote[core->lex_count2]) + 1;
			else
				core->lex_x += 2;
			core->lex_count2++;
		}
	}
}

void	lexing(char **splited, t_core *core)
{
	core->lex_i = -1;
	while (splited[++core->lex_i])
	{
		core->lex_n_quote = get_n_char(splited[core->lex_i], '\'');
		core->lex_n_d_quote = get_n_char(splited[core->lex_i], '\"');
		if (core->lex_n_d_quote == 0 && core->lex_n_quote == 0 && !core->lex_bool[QUOTE] && !core->lex_bool[D_QUOTE])
		{
			if (get_delimiter(splited[core->lex_i]))
				add_block(get_delimiter(splited[core->lex_i]), core, 1);
			else
				add_block(splited[core->lex_i], core, 0);
		}
		else
		{
			core->lex_x = 0;
			lexing2(splited, core);
			add_block(core->lex_join, core, 0);
			free(core->lex_join);
			core->lex_join = NULL;
		}
	}
}
