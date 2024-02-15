/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:36:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/15 21:25:12 by aallou-v         ###   ########.fr       */
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

void	middle_lexing(t_core *core, char **splited)
{
	(void) core;
	(void) splited;
}

int	first_lex(char *buf, t_core *core)
{
	core->lex_n_quote = get_n_char(buf[core->lex_i], '\'');
	core->lex_n_d_quote = get_n_char(buf[core->lex_i], '\"');
	if (core->lex_n_d_quote == 0 || core->lex_n_quote == 0)
		return (0);
	core->lex_x = -1;
	while (buf[++core->lex_x])
	{
		if (buf[core->lex_x] == '\'' &&!core->lex_bool[0] &&!core->lex_bool[1])
		{
			core->lex_bool[0] = 1;
			
		}
	}
	return (0);
}

void	lexing(char *buf, t_core *core)
{
	char	**splited;

	splited = ft_split(buf, ' ');
	while (splited[++core->lex_i])
	{
		if (core->lex_bool[0] || core->lex_bool[1] || first_lex(splited, core))
		{
			middle_lexing(core, splited[core->lex_i]);
			continue ;
		}
		if (get_delimiter(splited[core->lex_i]))
			add_block(get_delimiter(splited[core->lex_i]), core, 1);
		else
		{
			if (splited[core->lex_i][0] != '$')
				add_block(splited[core->lex_i], core, 0);
			else
				add_block(get_envp(ft_strchr(splited[core->lex_i],
							splited[core->lex_i][1]), core), core, 0);
		}
	}
	end_lexing(splited, core);
}

void	pre_lexing(char *buf, t_core *core)
{
	size_t	i;

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
		if (buf[i] == '$')
		{
			if (buf[i - 1] != ' ' && buf[i - 1] != '$')
				buf = add_char(buf, ' ', i);
		}
	}
	init_lexing(core);
	lexing(buf, core);
	free(buf);
}
