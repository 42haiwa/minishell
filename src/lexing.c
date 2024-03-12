/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:02:20 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/12 13:38:16 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			char	*substr;
			char	first;
			while (1)
			{
				first = get_first(splited[core->lex_i], "\'\"", core->lex_x);
				substr = get_substring(splited[core->lex_i], first, core->lex_x);
				core->lex_join = safe_join(core->lex_join, substr, 0, 1);
				core->lex_x += len_by_char(splited[core->lex_i], first, core->lex_x);
				if (first == 0)
					break ;
				if (first == '\'')
				{
					core->lex_join = safe_join(core->lex_join, core->get_quote[core->lex_count], 1, 0);
					if (core->get_quote[core->lex_count])
						core->lex_x += ft_strlen(core->get_quote[core->lex_count]) + 1;
					else
						core->lex_x += 2;
					core->lex_count++;
				}
				if (first == '\"')
				{
					core->lex_join = safe_join(core->lex_join, core->get_d_quote[core->lex_count2], 1, 0);
					if (core->get_d_quote[core->lex_count2])
						core->lex_x += ft_strlen(core->get_d_quote[core->lex_count2]) + 1;
					else
						core->lex_x += 2;
					core->lex_count2++;
				}
			}
			add_block(core->lex_join, core, 0);
			free(core->lex_join);
			core->lex_join = NULL;
		}
	}
}
