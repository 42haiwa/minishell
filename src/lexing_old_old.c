/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:36:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/08 10:02:09 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_lexing(char **splited, t_core *core)
{
	core->lex_i = 0;
	while (splited[core->lex_i])
	{
		free(splited[core->lex_i]);
		core->lex_i++;
	}
	free(splited);
}

void	lexing(char *buf, t_core *core, char **splited)
{
	char	*substr;
	
	(void) buf;
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
			if (!core->lex_bool[QUOTE] && !core->lex_bool[D_QUOTE] && splited[core->lex_i][0] != '\'' && splited[core->lex_i][0] != '"')
			{
				substr = get_substring(splited[core->lex_i], get_first(splited[core->lex_i], "\'\""));
				core->lex_join = safe_join(core->lex_join, substr);
				free(substr);
				printf("JOIN : %s\n", core->lex_join);
				if (get_first(splited[core->lex_i], "\'\"") == '\'')
				{
					core->lex_join = safe_join(core->lex_join, core->get_quote[core->lex_count]);
					core->lex_count++;
					core->lex_bool[QUOTE] = 1;
				}
				
			}
		}
	}
}

void	pre_lexing(char *buf, t_core *core)
{
	size_t	i;
	char	**splited;

	core->get_d_quote = get_double_quote(buf);
	core->get_quote = get_quote(buf);
	replace_main(core);
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '|' || buf[i] == ';' || buf[i] == '>' || buf[i] == '<')
		{
			if (buf[i + 1] != ' ')
				buf = add_char(buf, ' ', i + 1);
			if (i > 0 && buf[i - 1] != ' ')
				buf = add_char(buf, ' ', i);
		}
	}
	buf = init_lexing(core, buf);
	splited = ft_split(buf, ' ');
	lexing(buf, core, splited);
	end_lexing(splited, core);
	free(buf);
}
